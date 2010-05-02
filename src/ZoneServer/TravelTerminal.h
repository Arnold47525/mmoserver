/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TANGIBLE_TRAVELTERMINAL_H
#define ANH_ZONESERVER_TANGIBLE_TRAVELTERMINAL_H

#include "Terminal.h"

//=============================================================================

enum PortType
{
	portType_Starport		=	1,
	portType_Shuttleport	=	2
};

//=============================================================================

class TravelTerminal : public Terminal
{
	friend class TerminalFactory;

	public:

		TravelTerminal();
		~TravelTerminal();

		BString		getPosDescriptor(){ return mPositionDescriptor; }
		void		setPosDescriptor(const int8* desc){ mPositionDescriptor = desc; }

		PortType	getPortType(){ return mPortType; }
		void		setPortType(PortType portType){ mPortType = portType; }

		virtual void		handleObjectMenuSelect(uint8 messageType,Object* srcObject);

		virtual void		prepareCustomRadialMenu(CreatureObject* creatureObject, uint8 itemCount);

	private:

		BString		mPositionDescriptor;
		PortType	mPortType;

};

//=============================================================================

#endif

