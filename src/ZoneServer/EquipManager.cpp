/*
---------------------------------------------------------------------------------------
This source file is part of SWG:ANH (Star Wars Galaxies - A New Hope - Server Emulator)

For more information, visit http://www.swganh.com

Copyright (c) 2006 - 2010 The SWG:ANH Team
---------------------------------------------------------------------------------------
Use of this source code is governed by the GPL v3 license that can be found
in the COPYING file or at http://www.gnu.org/licenses/gpl-3.0.html

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
---------------------------------------------------------------------------------------
*/

#include "EquipManager.h"
#include "PlayerObject.h"
#include "MessageLib/MessageLib.h"
#include "Inventory.h"
#include "Object.h"
#include "Weapon.h"
#include "LogManager/LogManager.h"

//=============================================================================

EquipManager::EquipManager() :
mDefaultWeapon(NULL)
{
	mEquipSlots = 0;
}

//=============================================================================

EquipManager::~EquipManager()
{
	ObjectList* objList = getEquippedObjects();
	ObjectList::iterator it = objList->begin();

	while(it != objList->end())
	{
		if(gWorldManager->existObject((*it)))
		{
			gWorldManager->destroyObject((*it));
		}
		else
		{
			delete (*it);
		}
		it++;
	}

	delete objList;

	mSlotMap.clear();
	mObjectMap.clear();
}

ObjectList* EquipManager::getEquippedObjects()
{
	ObjectList* result = new ObjectList();
	ObjectSlotMap::iterator it = mObjectMap.begin();

	while(it != mObjectMap.end())
	{
		ObjectList::iterator ot = result->begin();

		bool hasObject = false;
		while(ot != result->end())
		{
			if((*ot) == (*it).first)
			{
				hasObject = true;
			}
			ot++;
		}

		if(!hasObject)
			result->push_front(it->first);


		it++;
	}

	return result;
}




//=============================================================================
//
// remove an object from all slots it occupies, returns nr of occurances removed
//

uint8 EquipManager::removeEquippedObject(Object* object)
{
	return removeEquippedObject(object->getEquipSlotMask());
}

//=============================================================================
//
// remove object(s) from the slotmask given
//

uint8 EquipManager::removeEquippedObject(uint64 slotMask)
{
	uint8 occurance = 0;

	for(uint64 slot = 1; slot < CREATURE_MAX_SLOT;slot = slot << 1)
	{
		if((slotMask & slot) == slot)
		{
			SlotMap::iterator	it = mSlotMap.find((CreatureEquipSlot)slot);

			if(it != mSlotMap.end())
			{
				Object*	object = (*it).second;

				freeEquipSlot((CreatureEquipSlot)slot);

				mSlotMap.erase(it);

				ObjectSlotMap::iterator ot = mObjectMap.find(object);
				if(ot != mObjectMap.end())
					mObjectMap.erase(ot);

				++occurance;
			}

		}
	}

	return(occurance);
}

//=============================================================================
//
// return an object by a slot given
//

Object* EquipManager::getEquippedObject(CreatureEquipSlot slot)
{
	SlotMap::iterator it = mSlotMap.find(slot);

	if(it != mSlotMap.end())
	{
		return((*it).second);
	}

	return(NULL);
}

/*
bool EquipManager::checkEquipObject(Object* object)
{
	SlotMap::iterator	it;
	uint32				slotMask	= object->getEquipSlotMask();

	// make sure we have a slot descriptor
	if(!slotMask)
	{
		return(false);
	}
	return true;
}
  */
//=============================================================================
//
// add an object according to its slot definitions, remove objects with slot conflicts
// the return is irrelevant as it does permanent changes anyway

bool EquipManager::addEquippedObject(Object* object)
{
	addEquippedObject(object->getEquipSlotMask(), object);
	return(true);
}

//=============================================================================
//
// add an object manually to the slots given, remove objects with slot conflicts
//

uint8 EquipManager::addEquippedObject(uint64 slotMask,Object* object)
{
	SlotMap::iterator	it;
	ObjectSlotMap::iterator ot;
	uint8			occurance = 0;

	for(uint64 slot = 1; slot < CREATURE_MAX_SLOT;slot = slot << 1)
	{
		if((slotMask & slot) == slot)
		{
			// free the occupied slot(s)
			it = mSlotMap.find((CreatureEquipSlot)slot);
			if(it != mSlotMap.end())
			{
				ot = mObjectMap.find(it->second);

				//Correct the First Map
				it->second = object;

				//Correct th Second Map
				mObjectMap.erase(ot);
				mObjectMap.insert(std::make_pair(object, (CreatureEquipSlot)slot));

				++occurance;
			}
			else
			{
				mSlotMap.insert(std::make_pair((CreatureEquipSlot)slot, object));
				mObjectMap.insert(std::make_pair(object, (CreatureEquipSlot)slot));
			}
		}
	}

	return(occurance);
}

//=============================================================================
bool EquipManager::equipDefaultWeapon()
{
	// make sure slot is empty
	if(getEquippedObject(CreatureEquipSlot_Hold_Left))
	{
		return(false);
		//removeEquippedObject(CreatureEquipSlot_Weapon);
	}

	// equip the default weapon
	addEquippedObject(CreatureEquipSlot_Hold_Left,mDefaultWeapon);
	return(true);
}

//=============================================================================

bool EquipManager::EquipItem(Object* object)
{
	if(!CheckEquipable(object))
		return false;
	
	PlayerObject*	owner		= dynamic_cast<PlayerObject*> (getParent());
	Item* item = dynamic_cast<Item*>(object);

	if(!item || !owner)
		return false;

	addEquippedObject(object);

	//equipped objects are always contained by the Player
	//unequipped ones by the inventory!

	uint64			parentId	= owner->getId();

	//update containment and db
	object->setParentId(parentId,4,owner,true);

	//create it for all nearby players
	PlayerObjectSet*	inRangePlayers	= owner->getKnownPlayers();
	gMessageLib->sendCreateTangible(item,inRangePlayers);

	//Update the Equipped List
	gMessageLib->sendEquippedListUpdate_InRange(owner);

	// weapon update
	if(item->getItemFamily() == ItemFamily_Weapon)
	{
		gMessageLib->sendWeaponIdUpdate(owner);
	}

	return true;
}

//=============================================================================

bool EquipManager::unEquipItem(Object* object)
{
	Item* item = dynamic_cast<Item*>(object);
	if(!item)
	{
		gLogger->log(LogManager::DEBUG,"Inventory::unEquipItem : No Item object ID : %"PRIu64"",object->getId());
		return false;
	}

	PlayerObject*	owner		= dynamic_cast<PlayerObject*> (this->getParent());
	if(!owner)
	{
		gLogger->log(LogManager::DEBUG,"Inventory::unEquipItem : No one has it equipped");
		return false;
	}

	//client forces us to stop performing at this point as he unequips the instrument regardless of what we do
	if((item->getItemFamily() == ItemFamily_Instrument) && (owner->getPerformingState() != PlayerPerformance_None))
	{
		gEntertainerManager->stopEntertaining(owner);
	}

	//equipped objects are always contained by the Player
	//unequipped ones by the inventory!

	Inventory*		inventory		=	dynamic_cast<Inventory*>(getEquippedObject(CreatureEquipSlot_Inventory));
	uint64			parentId		=	inventory->getId();

	//the object is now in the inventory
	//update the containment for owner and db
	object->setParentId(inventory->getId(), 0xffffffff, owner, true);
	
	//destroy for everyone in range
	gMessageLib->sendDestroyObject_InRange(object->getId(),owner,false);
	gMessageLib->sendEquippedListUpdate_InRange(owner);

	//and add to inventories regular (unequipped) list
	//this->addObjectSecure(object); the transferhandler will put it wherever necessary

	removeEquippedObject(object);

	//check whether the hairslot is now free
	TangibleObject*				playerHair		= dynamic_cast<TangibleObject*>(owner->getHair());//dynamic_cast<TangibleObject*>(customer->getEquipManager()->getEquippedObject(CreatureEquipSlot_Hair));
	TangibleObject*				playerHairSlot	= dynamic_cast<TangibleObject*>(getEquippedObject(CreatureEquipSlot_Hair));
	if((!playerHairSlot)&&playerHair)
	{
		//if we have hair equip it
		addEquippedObject(CreatureEquipSlot_Hair,playerHair);
	}

	// if we unequiped our weapon, set the unarmed default weapon
	if(item->getItemFamily() == ItemFamily_Weapon && (item->getEquipSlotMask() & CreatureEquipSlot_Hold_Left) == CreatureEquipSlot_Hold_Left)
	{
		equipDefaultWeapon();
	}

	if(item->getItemFamily() == ItemFamily_Weapon)
	{
		gMessageLib->sendWeaponIdUpdate(owner);
	}

	return true;
}
//=============================================================================

bool EquipManager::CheckEquipable(Object* object)
{
	Item* item = dynamic_cast<Item*>(object);
	PlayerObject*	owner		= dynamic_cast<PlayerObject*> (getParent());

	if(!item)
	{
		gLogger->log(LogManager::DEBUG,"Inventory::EquipItem : No Item object ID : %I64u",object->getId());
		return(false);
	}
	
	if(!owner)
	{
		gLogger->log(LogManager::DEBUG,"Inventory::EquipItem : No owner");
		return(false);
	}
	
	// don't equip music instruments or weapons while performing

	if((owner->getPerformingState())&&((item->getItemFamily() == ItemFamily_Instrument) || (item->getItemFamily() == ItemFamily_Weapon)))
	{
		return(false);
	}

	// check items equip restrictions, first check race and gender
	uint64 filter1 = item->getEquipRestrictions() & 0xFFF;
	uint64 filter2 = owner->getRaceGenderMask() & 0xFFF;

	if((filter1 & filter2) != filter2)
	{
		gMessageLib->sendSystemMessage(owner,L"You can't equip this item.");
		return(false);
	}

	// then check, if we need to be jedi
	filter1 = item->getEquipRestrictions() & 0xF000;
	filter2 = owner->getRaceGenderMask() & 0xF000;

	if(filter1 && !filter2)
	{
		gMessageLib->sendSystemMessage(owner,L"You can't equip this item.");
		return(false);
	}

	// then faction
	filter1 = item->getEquipRestrictions() & 0xF0000;

	if((filter1 == 0x10000 && strcmp(owner->getFaction().getAnsi(),"rebel") != 0)
	|| (filter1 == 0x20000 && strcmp(owner->getFaction().getAnsi(),"imperial") != 0))
	{
		gMessageLib->sendSystemMessage(owner,L"You can't equip this item.");
		return(false);
	}

	uint64 filter3 = CreatureEquipSlot_Datapad & CreatureEquipSlot_Bank & CreatureEquipSlot_Inventory & CreatureEquipSlot_Mission;
	if(filter3 && item->getEquipSlotMask())
	{
		gMessageLib->sendSystemMessage(owner,L"Attention!!! the Equip - BitMask is messedup.");
		return(false);
	}
	return true;
}
