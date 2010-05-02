/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TANGIBLE_PLAYERSTRUCTURETERMINAL_H
#define ANH_ZONESERVER_TANGIBLE_PLAYERSTRUCTURETERMINAL_H

#include "Terminal.h"


//=============================================================================

class PlayerStructureTerminal : public Terminal
{
	friend class TerminalFactory;

	public:

		PlayerStructureTerminal();
		~PlayerStructureTerminal();

		void		handleObjectMenuSelect(uint8 messageType,Object* srcObject);
		void		handleUIEvent(uint32 action,int32 element,BString inputStr,UIWindow* window);

		void		prepareCustomRadialMenu(CreatureObject* player, uint8 itemCount);

		void		setStructure(uint64 s){mStructure = s;}
		uint64		getStructure(){return mStructure;}

	private:
		
		
		uint64			mStructure;

};

//=============================================================================

#endif

