/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_TREASURYMANAGER_H
#define ANH_ZONESERVER_TREASURYMANAGER_H

#define 	gTreasuryManager	TreasuryManager::getSingletonPtr()

#include "RadialMenu.h"

#include "Utils/typedefs.h"
#include "DatabaseManager/DatabaseCallback.h"

#if defined(__GNUC__)
// GCC implements tr1 in the <tr1/*> headers. This does not conform to the TR1
// spec, which requires the header without the tr1/ prefix.
#include <tr1/memory>
#else
#include <memory>
#endif

//======================================================================================================================

class CreatureObject;
class Database;
class DatabaseCallback;
class DatabaseResult;
class DispatchClient;
class PlayerObject;

//======================================================================================================================

enum TREMQueryType
{
	TREMQuery_NULL					=	0,
	TREMQuery_BankTipgetId			=	1,
	TREMQuery_BankTipTransaction	=	2

};

//======================================================================================================================

class TreasuryManagerAsyncContainer
{

	public:

		TreasuryManagerAsyncContainer(TREMQueryType qt,DispatchClient* client){ mQueryType = qt; mClient = client; }
		~TreasuryManagerAsyncContainer(){}

		TREMQueryType		mQueryType;
		DispatchClient*		mClient;

		uint32				amount;
		PlayerObject*		player;
		PlayerObject*		target;
		uint64				targetId;
		BString				targetName;
};

//======================================================================================================================

class TreasuryManager : public DatabaseCallback
{
	public:

		TreasuryManager(Database* database);
		~TreasuryManager();

		static TreasuryManager*		    Init(Database* database);
		static TreasuryManager*		    getSingletonPtr() { return mSingleton; }

		virtual void				    handleDatabaseJobComplete(void* ref,DatabaseResult* result);

		void						    bankDepositAll(PlayerObject* playerObject);
		void						    bankWithdrawAll(PlayerObject* playerObject);
		void						    bankTransfer(int32 inventoryMoneyDelta, int32 bankMoneyDelta, PlayerObject* playerObject);
        std::tr1::shared_ptr<RadialMenu>   bankBuildTerminalRadialMenu(CreatureObject* creatureObject);
		void						    bankOpenSafetyDepositContainer(PlayerObject* playerObject);
		void						    bankQuit(PlayerObject* playerObject);
		void						    bankJoin(PlayerObject* playerObject);

		void						    saveAndUpdateInventoryCredits(PlayerObject* playerObject);
		void						    saveAndUpdateBankCredits(PlayerObject* playerObject);

		//handles bank tip to offline player
		void						    bankTipOffline(int32 amount, PlayerObject* playerObject, BString targetName);
		void						    inventoryTipOnline(int32 amount, PlayerObject* playerObject, PlayerObject* targetObject );
		void						    bankTipOnline(int32 amount, PlayerObject* playerObject, PlayerObject* targetObject );

	private:

		static bool					mInsFlag;
		static TreasuryManager*		mSingleton;
		Database*					mDatabase;
};

#endif
