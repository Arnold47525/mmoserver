/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TANGIBLE_TICKETCOLLECTOR_H
#define ANH_ZONESERVER_TANGIBLE_TICKETCOLLECTOR_H

#include "TangibleObject.h"

//=============================================================================

class Shuttle;
class TravelTicket;

//=============================================================================

class TicketCollector : public TangibleObject
{
	friend class TicketCollectorFactory;

	public:

		TicketCollector();
		~TicketCollector();

		virtual void	handleObjectMenuSelect(uint8 messageType,Object* srcObject);
		virtual void	prepareCustomRadialMenu(CreatureObject* creatureObject, uint8 itemCount);

		void			setShuttle(Shuttle* shuttle){ mShuttle = shuttle; }
		Shuttle*		getShuttle(){ return mShuttle; }

		void			setPortDescriptor(BString des){ mPortDescriptor = des; }
		BString			getPortDescriptor(){ return mPortDescriptor; }

		void			travelRequest(TravelTicket* ticket,PlayerObject* playerObject);

		virtual void	handleUIEvent(uint32 action,int32 element,BString inputStr,UIWindow* window);

	private:

		void			_createTicketSelectMenu(PlayerObject* playerObject);

		Shuttle*		mShuttle;
		BString			mPortDescriptor;

};

//=============================================================================

#endif
