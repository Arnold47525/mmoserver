/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_CHATSERVER_PLAYER_H
#define ANH_CHATSERVER_PLAYER_H

#include "Utils/typedefs.h"
#include <map>

class DispatchClient;

//======================================================================================================================

typedef std::map<uint32,BString> ContactMap;

//======================================================================================================================

struct Bazaar
{
		uint64			ownerid;
		uint64			id;
		uint32			regionid;
		uint32			planetid;
		int8			string[128];
		int8			planet[32];
		int8			region[48];
};

struct PlayerData
{
		BString name;
		BString last_name;
};

class Player
{
public:
	Player(uint64 charId,DispatchClient* client,uint32 planetId)
		: mBazaar(NULL)
		, mClient(client)
		, mCharId(charId)
		, mGroupId(0)
		, mKey(NULL)
		, mPlanetId(planetId)
		, mX(0)
		, mZ(0)
		, mGroupMemberIndex(0)
		, mAddPending(true)
	{}

	~Player()
	{}

	uint64			getCharId(){ return mCharId; }
	void			setCharId(uint64 charId){ mCharId = charId; }

	BString&			getName(){ return mPlayerData.name; }
	void			setName(const BString name){ mPlayerData.name = name; }

	PlayerData* getPlayerData() { return &mPlayerData; }
	BString&			getLastName(){ return mPlayerData.last_name; }
	void			setLastName(const BString lastName){ mPlayerData.last_name = lastName; }

	DispatchClient*	getClient(){ return mClient; }
	void			setClient(DispatchClient* client){ mClient = client; }

	uint32			getPlanetId(){ return mPlanetId; }
	void			setPlanetId(uint32 planetId){ mPlanetId = planetId; }

	bool			getAddPending(){ return mAddPending; }
	void			setAddPending(bool b){ mAddPending = b; }

	uint32			getKey(){ return mKey; }
	void			setKey() { BString name = getName(); name.toLower(); mKey = name.getCrc(); }

	ContactMap*		getFriendsList(){ return &mFriendsList; }
	void			addFriend(BString name){ mFriendsList.insert(std::make_pair(name.getCrc(),name.getAnsi())); }
	void			removeFriend(uint32 nameCrc);
	bool			checkFriend(uint32 nameCrc);

	ContactMap*		getIgnoreList(){ return &mIgnoreList; }
	void			addIgnore(BString name){ mIgnoreList.insert(std::make_pair(name.getCrc(),name.getAnsi())); }
	void			removeIgnore(uint32 nameCrc);
	bool			checkIgnore(uint32 nameCrc);

	uint16			getGroupMemberIndex(){ return mGroupMemberIndex; }
	void			setGroupMemberIndex(uint16 index){ mGroupMemberIndex = index; }

	uint64			getGroupId(){ return mGroupId; }
	void			setGroupId(uint64 groupId){ mGroupId = groupId; }

	void			setPositionX(float position) {mX = position; }
	float			getPositionX() {return mX;}

	void			setBazaar(Bazaar* bazaar) {mBazaar = bazaar; }
	Bazaar*			getBazaar() {return mBazaar;}

	void			setPositionZ(float position) {mZ = position; }
	float			getPositionZ() {return mZ;}

private:
	ContactMap			mFriendsList,mIgnoreList;
	PlayerData  		mPlayerData;
	Bazaar*		    	mBazaar;
	DispatchClient*	mClient;
	uint64					mCharId;
	uint64					mGroupId;
	uint32					mKey;
	uint32					mPlanetId;
	float						mX;
	float						mZ;
	uint16					mGroupMemberIndex;
	bool						mAddPending;
};

#endif

