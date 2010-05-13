/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/
#include "MissionManager.h"
#include "ObjectController.h"
#include "ObjectControllerOpcodes.h"
#include "ObjectControllerCommandMap.h"
#include "PlayerObject.h"
#include "LogManager/LogManager.h"
#include "DatabaseManager/Database.h"
#include "DatabaseManager/DataBinding.h"
#include "DatabaseManager/DatabaseResult.h"
#include "Common/Message.h"
#include "Common/MessageFactory.h"




//=============================================================================================================================
//
// mission list request
//

void ObjectController::handleMissionListRequest(Message* message)
{
    PlayerObject*   player  = dynamic_cast<PlayerObject*>(mObject);

    /*uint8           unknown     = */message->getUint8();
    uint8           stale_flag  = message->getUint8();
    uint64          terminal_id = message->getUint64();

	#if defined(_DEBUG)
		gLogger->logMsgF("START :: Terminal id %"PRIu64" \n", MSG_NORMAL, terminal_id);
	#endif

    gMissionManager->listRequest(player, terminal_id,stale_flag);
	
	#if defined(_DEBUG)
		gLogger->logMsgF("END :: Terminal id %"PRIu64" \n", MSG_NORMAL, terminal_id);
	#endif
}

//=============================================================================================================================

//NOTE: Client never sends this... - meanmon13
void ObjectController::handleMissionDetailsRequest(Message* message)
{
    PlayerObject*   player  = dynamic_cast<PlayerObject*>(mObject);

    gMissionManager->detailsRequest(player);


}

//=============================================================================================================================

void ObjectController::handleMissionCreateRequest(Message* message)
{
    PlayerObject*   player  = dynamic_cast<PlayerObject*>(mObject);

    gMissionManager->createRequest(player);

}

//=============================================================================================================================

void ObjectController::handleGenericMissionRequest(Message* message)
{
    PlayerObject*   player  = dynamic_cast<PlayerObject*>(mObject);
	uint64 mission_id = message->getUint64();

    gMissionManager->missionRequest(player, mission_id);

}

//=============================================================================================================================

void ObjectController::handleMissionAbort(Message* message)
{
	PlayerObject*   player  = dynamic_cast<PlayerObject*>(mObject);
	uint64 mission_id = message->getUint64();

	gMissionManager->missionAbort(player, mission_id);


}

//=============================================================================================================================

