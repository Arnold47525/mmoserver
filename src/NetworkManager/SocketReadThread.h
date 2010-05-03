/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_NETWORKMANAGER_SOCKETREADTHREAD_H
#define ANH_NETWORKMANAGER_SOCKETREADTHREAD_H

#include "Utils/typedefs.h"

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <list>
#include <map>

	
//======================================================================================================================

class SocketWriteThread;
class PacketFactory;
class SessionFactory;
class MessageFactory;
class CompCryptor;
class Session;
class Service;
class Packet;

//======================================================================================================================

typedef std::list<Session*>			SessionList;
typedef std::map<uint64,Session*>	AddressSessionMap;     
				                                                                     
typedef int SOCKET;

//======================================================================================================================

class NewConnection
{
	public:

	  int8              mAddress[256];
	  uint16            mPort;
	  Session*          mSession;
};

//======================================================================================================================

class SocketReadThread
{
	public:
									SocketReadThread(SOCKET socket, SocketWriteThread* writeThread, Service* service,uint32 mfHeapSize, bool serverservice);
									~SocketReadThread();

	  virtual void					run();

	  void                          NewOutgoingConnection(int8* address, uint16 port);
	  void                          RemoveAndDestroySession(Session* session);

	  NewConnection*                getNewConnectionInfo(void)  { return &mNewConnection; };
	  bool                          getIsRunning(void)          { return mIsRunning; }
	  void							requestExit()				{ mExit = true; }

	protected:

	  void                          _startup(void);
	  void                          _shutdown(void);

	  Packet*                       mReceivePacket;
	  Packet*                       mDecompressPacket;

	  uint16						mMessageMaxSize;
	  SocketWriteThread*            mSocketWriteThread;
	  SessionFactory*               mSessionFactory;
	  PacketFactory*                mPacketFactory;
	  MessageFactory*               mMessageFactory;
	  CompCryptor*                  mCompCryptor;
	  NewConnection                 mNewConnection;

	  SOCKET                        mSocket;

	  bool							mIsRunning;

	  uint32						mSessionResendWindowSize;
      boost::thread 				mThread;
      boost::mutex					mSocketReadMutex;
	  AddressSessionMap             mAddressSessionMap;
	  
	  bool							mExit;
};

//======================================================================================================================

#endif //ANH_NETWORKMANAGER_SOCKETREADTHREAD_H



