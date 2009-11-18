
/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2009 The swgANH Team

---------------------------------------------------------------------------------------
*/
#include "HarvesterObject.h"
#include "PlayerObject.h"
#include "StructureManager.h"
#include "UIManager.h"
#include "MathLib/Quaternion.h"

//=============================================================================

HarvesterObject::HarvesterObject() : PlayerStructure()
{
	mType = ObjType_Harvester;
	
}

//=============================================================================

HarvesterObject::~HarvesterObject()
{

}

//=============================================================================
//handles the radial selection

void HarvesterObject::handleObjectMenuSelect(uint8 messageType,Object* srcObject)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(srcObject);
	if(!player)
	{	
		gLogger->logMsgF("HarvesterObject::handleObjectMenuSelect::could not find player",MSG_HIGH);
		return;
	}
	
	switch(messageType)
	{
		case radId_serverTerminalManagementDestroy: 
		{
			StructureAsyncCommand command;
			command.Command = Structure_Command_Destroy;
			command.PlayerId = player->getId();
			command.StructureId = this->getId();

			gStructureManager->checkNameOnPermissionList(this->getId(),player->getId(),player->getFirstName().getAnsi(),"ADMIN",command);
			
		}
		break;
		case radId_serverTerminalPermissionsAdmin:
		{			
			StructureAsyncCommand command;
			command.Command = Structure_Command_PermissionAdmin;
			command.PlayerId = player->getId();
			command.StructureId = this->getId();

			gStructureManager->checkNameOnPermissionList(this->getId(),player->getId(),player->getFirstName().getAnsi(),"ADMIN",command);

		}
		break;

		case radId_serverTerminalPermissionsHopper:
		{			
			StructureAsyncCommand command;
			command.Command = Structure_Command_PermissionHopper;
			command.PlayerId = player->getId();
			command.StructureId = this->getId();

			gStructureManager->checkNameOnPermissionList(this->getId(),player->getId(),player->getFirstName().getAnsi(),"ADMIN",command);

		}
		break;

		case radId_setName:
		{

			gUIManager->createRenameStructureBox(this,player, this);
		}
		break;

		
	}
}

void HarvesterObject::prepareCustomRadialMenu(CreatureObject* creatureObject, uint8 itemCount)
{
	PlayerObject* player = dynamic_cast<PlayerObject*>(creatureObject);
	if(!player)
	{	
		gLogger->logMsgF("HarvesterObject::handleObjectMenuSelect::could not find player",MSG_HIGH);
		return;
	}
	
	RadialMenu* radial	= new RadialMenu();
			
	//radId_serverHarvesterManage
	//radId_serverHouseManage
	radial->addItem(1,0,radId_examine,radAction_Default,"");
	radial->addItem(2,0,radId_serverHarvesterManage,radAction_ObjCallback,"Structure Management");
	radial->addItem(3,0,radId_serverTerminalManagement,radAction_ObjCallback,"Structure Permissions");
	
	radial->addItem(4,2,radId_serverTerminalManagementDestroy,radAction_ObjCallback,"destroy");//destroy
	radial->addItem(5,2,radId_setName,radAction_ObjCallback,"Rename Structure");//destroy
	
	radial->addItem(6,3,radId_serverTerminalPermissionsAdmin,radAction_ObjCallback,"Admin List");//destroy
	radial->addItem(7,3,radId_serverTerminalPermissionsHopper,radAction_ObjCallback,"Hopper List");//destroy
	


	RadialMenuPtr radialPtr(radial);
	mRadialMenu = radialPtr;
}

/*

void HarvesterObject::handleUIEvent(uint32 action,int32 element,string inputStr,UIWindow* window)
{

	PlayerObject* playerObject = window->getOwner();

	if(!playerObject || action || playerObject->getSurveyState() || playerObject->getSamplingState() || playerObject->isIncapacitated() || playerObject->isDead())
	{
		return;
	}

	switch(window->getWindowType())
	{

		case SUI_Window_Structure_Delete:
		{
		}
		break;

	}
}
*/