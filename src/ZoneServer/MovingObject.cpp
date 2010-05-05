/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#include "CellObject.h"
#include "Datapad.h"
#include "MessageLib/MessageLib.h"
#include "MovingObject.h"
#include "PlayerObject.h"
#include "QuadTree.h"
#include "VehicleController.h"
#include "WorldManager.h"
#include "ZoneTree.h"

//=============================================================================

MovingObject::MovingObject()
: Object()
, mInMoveCount(0)
, mBaseAcceleration(1.50f)
, mBaseRunSpeedLimit(5.75f)
, mBaseTerrainNegotiation(1.0f)
, mBaseTurnRate(1.0f)
, mCurrentRunSpeedLimit(5.75f)
, mCurrentSpeed(0.0f)
, mCurrentTerrainNegotiation(1.0f)
, mCurrentTurnRate(1.0f)
, mCurrentSpeedMod(1.0f)
, mBaseSpeedMod(1.0f)
{
}

//=============================================================================

MovingObject::~MovingObject()
{
}

//=============================================================================

void MovingObject::faceObject(Object* object_to_face)
{	
    // Create a mirror direction vector for the direction we want to face.
    glm::vec3 direction_vector = glm::normalize(object_to_face->mPosition - mPosition);
    direction_vector.x = -direction_vector.x;

    // Create a lookat matrix from the direction vector and convert it to a quaternion.
    mDirection = glm::toQuat(glm::lookAt(
        direction_vector, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)
        ));

    // If in the 3rd quadrant the signs need to be flipped.
    if (mDirection.y <= 0.0f && mDirection.w >= 0.0f) {
        mDirection.y = -mDirection.y;
        mDirection.w = -mDirection.w;
    }
}

//=============================================================================

//=============================================================================
//
//	Update npc position in game world.
//

void MovingObject::updatePositionOutside(uint64 parentId, const glm::vec3& newPosition)
{
	//we have been inside - move us outside
	if (this->getParentId() != 0)
	{
		// if we just left a building we need to update our containment - send a zero to uncontain us from that old cell
		if (!this->getKnownPlayers()->empty())
		{
			gMessageLib->broadcastContainmentMessage(this,this->getParentId(),0);
		}

		// remove us from the last cell we were in
		if (CellObject* cell = dynamic_cast<CellObject*>(gWorldManager->getObjectById(this->getParentId())))
		{
			cell->removeObject(this);
		}
		else
		{
			gLogger->logMsgF("Error removing %"PRIu64" from cell(%"PRIu64")",MSG_HIGH,this->getId(),this->getParentId());
		}

		// now set our new ParentId
		this->setParentId(0);

		//and update the position
		this->mPosition = newPosition;

		// Add us to the world and set our new containment for all watchers
		if (!this->getKnownPlayers()->empty())
		{
			gMessageLib->broadcastContainmentMessage(this,0,4);
		}

		// add us to the qtree
		if (QTRegion* newRegion = gWorldManager->getSI()->getQTRegion((double)this->mPosition.x,(double)this->mPosition.z))
		{
			this->setSubZoneId((uint32)newRegion->getId());
			newRegion->mTree->addObject(this);
		}
		else
		{
			// we should never get here !
			gLogger->logMsg("NPCObject::updatePosition: could not find zone region in map");
		}
	}
	else
	{
		// We have been outside

		// get the qt of the new position
		// if (QTRegion* newRegion = gWorldManager->getSI()->getQTRegion((double)this->mPosition.x,(double)this->mPosition.z))
		if (QTRegion* newRegion = gWorldManager->getSI()->getQTRegion((double)newPosition.x, (double)newPosition.z))
		{
			// we didnt change so update the old one
			if((uint32)newRegion->getId() == this->getSubZoneId())
			{
				// this also updates the object (npcs) position
				newRegion->mTree->updateObject(this, newPosition);

				if(PlayerObject* player = dynamic_cast<PlayerObject*>(this))
				{
					if(player->checkIfMounted() && player->getMount())
					{
						newRegion->mTree->updateObject(player->getMount(),newPosition);
					}
				}
			}
			else
			{
				// remove from old
				if (QTRegion* oldRegion = gWorldManager->getQTRegion(this->getSubZoneId()))
				{
					oldRegion->mTree->removeObject(this);
				}

				// put into new
				this->mPosition = newPosition;
				this->setSubZoneId((uint32)newRegion->getId());
				newRegion->mTree->addObject(this);
			}
		}
	}
}

void MovingObject::updatePositionInCell(uint64 parentId, const glm::vec3& newPosition)
{
	uint64 oldParentId = this->getParentId();
	if (oldParentId != parentId)
	{
		// We changed cell
		CellObject* cell = NULL;

		// Remove us.
		if (!this->getKnownPlayers()->empty())
		{
			gMessageLib->broadcastContainmentMessage(this,oldParentId,0);
		}
		// gLogger->logMsgF("NPC changed cell from (%"PRIu64") to (%"PRIu64")",MSG_NORMAL, oldParentId, parentId);

		// only remove us from si, if we just entered the building
		if (oldParentId != 0)
		{
			// We are still inside.
			if ((cell = dynamic_cast<CellObject*>(gWorldManager->getObjectById(oldParentId))))
			{
				cell->removeObject(this);
			}
			else
			{
				gLogger->logMsgF("Error removing %"PRIu64" from cell(%"PRIu64")",MSG_NORMAL,this->getId(),oldParentId);
			}
		}
		else
		{
			// remove us from qt
			// We just entered a building.
			if (this->getSubZoneId())
			{
				if (QTRegion* region = gWorldManager->getQTRegion(this->getSubZoneId()))
				{
					this->setSubZoneId(0);
					region->mTree->removeObject(this);
				}
			}
		}

		// put us into new one
		if (!this->getKnownPlayers()->empty())
		{
			gMessageLib->broadcastContainmentMessage(this,parentId,4);
		}
		if ((cell = dynamic_cast<CellObject*>(gWorldManager->getObjectById(parentId))))
		{
			cell->addObjectSecure(this);
		}
		else
		{
			gLogger->logMsgF("Error adding %"PRIu64" to cell(%"PRIu64")",MSG_NORMAL,this->getId(),parentId);
		}
		// update the player
		this->setParentId(parentId);
	}
}

void MovingObject::updatePosition(uint64 parentId, const glm::vec3& newPosition)
{
	// gLogger->logMsgF("NPCObject::updatePosition: update NPC position)", MSG_NORMAL);

	if (parentId == 0)
	{
		//we are to be moved (or already are) outside
		updatePositionOutside(parentId, newPosition);
	}
	else
	{
		updatePositionInCell(parentId, newPosition);	
	}

	this->mPosition = newPosition;

	//TODO do we need to update our known Objects ???
	//answer YES if we are a player 
	bool isPlayer = false;
	
	if(PlayerObject* player = dynamic_cast<PlayerObject*>(this))
	{
		isPlayer = true;
		//we cannot stop entertaining here, as the entertainermanager uses this code to move us to the placed instrument
		
		player->getController()->playerWorldUpdate(true);

		//dismount us if we were moved inside
		if(player->checkIfMounted() && player->getMount() && parentId)
		{
			Datapad* datapad = dynamic_cast<Datapad*>(player->getEquipManager()->getEquippedObject(CreatureEquipSlot_Datapad));

			if(datapad)
			{
				if(VehicleController* datapad_pet = dynamic_cast<VehicleController*>(datapad->getDataById(player->getMount()->getPetController())))
				{
					datapad_pet->dismountPlayer();
					datapad_pet->store();
				}
			}
		}
	}

	// send out position updates to known players
	this->incInMoveCount();

	//check whether updates are necessary before building the packet and then destroying it
	if ((!isPlayer) && this->getKnownPlayers()->empty())
	{
		return;
	}

	if (this->getParentId())
	{
		// We are inside a cell.

		//needs to be 0000000B as unknown int otherwise the datatransform gets ignored
		gMessageLib->sendDataTransformWithParent0B(this);

		gMessageLib->sendUpdateTransformMessageWithParent(this);
	}
	else
	{
		gMessageLib->sendDataTransform(this);
		gMessageLib->sendUpdateTransformMessage(this);
	}
}
