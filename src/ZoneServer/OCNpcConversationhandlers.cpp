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
#include "BankTerminal.h"
#include "ConversationManager.h"
#include "CraftingTool.h"
#include "CurrentResource.h"
#include "FillerNPC.h"
#include "Item.h"
#include "MissionManager.h"
#include "NPCObject.h"
#include "ObjectController.h"
#include "ObjectControllerOpcodes.h"
#include "ObjectControllerCommandMap.h"
#include "PlayerObject.h"
#include "SurveyTool.h"
#include "TravelMapHandler.h"
#include "UIManager.h"
#include "Wearable.h"
#include "WorldConfig.h"
#include "WorldManager.h"

#include "MessageLib/MessageLib.h"
#include "LogManager/LogManager.h"
#include "DatabaseManager/Database.h"
#include "DatabaseManager/DatabaseResult.h"
#include "DatabaseManager/DataBinding.h"
#include "Common/MessageFactory.h"
#include "Common/Message.h"

#include "Utils/clock.h"

//=============================================================================
//
// conversation start
//

void ObjectController::_handleNPCConversationStart(uint64 targetId,Message* message,ObjectControllerCmdProperties* cmdProperties)
{
	PlayerObject*	player	= dynamic_cast<PlayerObject*>(mObject);
	NPCObject*		npc		= dynamic_cast<NPCObject*>(gWorldManager->getObjectById(targetId));

	if(npc)
	{
		// in range check
		uint64 playerParentId	= player->getParentId();
		uint64 npcParentId		= npc->getParentId();
		bool   inRange			= true;

		// not inside same parent, or out of range
		if(!playerParentId && !npcParentId)
		{
            if (glm::distance(player->mPosition, npc->mPosition) > 10.0f)
			{
				inRange = false;
			}
		}
		// both inside a building
		else if(playerParentId && npcParentId)
		{
			uint64 playerBuildingId = gWorldManager->getObjectById(playerParentId)->getParentId();
			uint64 npcBuildingId	= gWorldManager->getObjectById(npcParentId)->getParentId();

			// not inside same building, or out of range
            if(playerBuildingId != npcBuildingId || (glm::distance(player->mPosition, npc->mPosition) > 10.0f))
			{
				inRange = false;
			}
		}

		// we are out of range
		if(!inRange)
		{
            float distance = glm::distance(player->mPosition, npc->mPosition);
			char buffer[100];
			sprintf(buffer, "You are out of range (%f m).", distance);
			string msg(buffer);
			msg.convert(BSTRType_Unicode16);
			gMessageLib->sendSystemMessage(player,msg);
			// gMessageLib->sendSystemMessage(player,L"","system_msg","out_of_range");
			return;
		}

		//check to see if he is part of a mission
		if(gMissionManager->checkDeliverMission(player,npc) ||
		   gMissionManager->checkCraftingMission(player,npc)
		  ) return;		

		// we don't want him to talk
		if(npc->hasInternalAttribute("no_chat"))
		return;

		// initiate a conversation dialog
		if(npc->hasInternalAttribute("base_conversation"))
		{
			// Let the npc have your attention, and some npc-movement.
			npc->prepareConversation(player);
			gConversationManager->startConversation(npc,player);
		}

		// say some chatter
		else
		{
			// spam protection
			uint64 localTime = Anh_Utils::Clock::getSingleton()->getLocalTime();
			if(npc->getLastConversationTarget() == player->getId())
			{
				if(localTime - npc->getLastConversationRequest() < NPC_CHAT_SPAM_PROTECTION_TIME)
				{
					return;
				}
				else
				{
					npc->setLastConversationRequest(localTime);
				}
			}
			else
			{
				npc->setLastConversationRequest(localTime);
				npc->setLastConversationTarget(player->getId());
			}

			// Let the npc have your attention, and some npc-movement.
			// Nope... npc->prepareConversation(player);

			// say a specific preset sentence
			if(npc->hasInternalAttribute("npc_chat"))
			{
				char quack[5][32];
				memset(quack, 0, sizeof(quack));

				string phrase = (int8*)(npc->getInternalAttribute<std::string>("npc_chat").c_str());
				phrase.convert(BSTRType_Unicode16);

				if (!gWorldConfig->isInstance())
				{
					gMessageLib->sendSpatialChat(npc,phrase,quack);
				}
				else
				{
					gMessageLib->sendSpatialChat(npc,phrase,quack, player);
				}
			}

			// say a random phrase
			else
			{
				char quack[5][32];
				memset(quack, 0, sizeof(quack));
				std::pair<string,uint32> chat = gWorldManager->getRandNpcChatter();

				if (!gWorldConfig->isInstance())
				{
					gMessageLib->sendSpatialChat(npc,chat.first,quack);
					if(chat.second)
					{
						gMessageLib->sendCreatureAnimation(npc,gWorldManager->getNpcConverseAnimation(chat.second));
					}
				}
				else
				{
					gMessageLib->sendSpatialChat(npc,chat.first,quack, player);
					if(chat.second)
					{
						gMessageLib->sendCreatureAnimation(npc,gWorldManager->getNpcConverseAnimation(chat.second), player);
					}
				}
			}
		}
	}
	else
		gLogger->log(LogManager::DEBUG,"ObjController::_handleNPCConversationStart: Couldn't find object %"PRIu64"",targetId);
}

//=============================================================================
//
// conversation stop
//

void ObjectController::_handleNPCConversationStop(uint64 targetId,Message* message,ObjectControllerCmdProperties* cmdProperties)
{
	PlayerObject*	playerObject = dynamic_cast<PlayerObject*>(mObject);

	gConversationManager->stopConversation(playerObject);
}

//=============================================================================
//
// conversation select
//

void ObjectController::_handleNPCConversationSelect(uint64 targetId,Message* message,ObjectControllerCmdProperties* cmdProperties)
{
	PlayerObject*	playerObject	= dynamic_cast<PlayerObject*>(mObject);
	string			dataStr;
	uint32			selectId		= 0;

	message->getStringUnicode16(dataStr);

	if(swscanf(dataStr.getUnicode16(),L"%u",&selectId) != 1)
	{
		gLogger->log(LogManager::DEBUG,"ObjController::handleNPCConversationSelect: Error in parameters\n");
		return;
	}

	gConversationManager->updateConversation(selectId,playerObject);
}

//=============================================================================


