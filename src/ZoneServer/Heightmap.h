/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_HEIGHTMAP_H
#define ANH_ZONESERVER_HEIGHTMAP_H

// #define     gHeightmap    Heightmap::getSingletonPtr()

#include "Utils/typedefs.h"
// lockfree_queue doesn't seem to be used - Xunil
//#include "Utils/lockfree_queue.h"
#include <boost/thread/thread.hpp>
#include <string>
#include "HeightmapAsyncContainer.h"
#include <queue>

class Heightmap
{

	public:
		static Heightmap*  Instance(void);
		static void deleter(void)
		{
			if (mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}

		void addNewHeightMapJob(HeightmapAsyncContainer* container) {mJobMutex.lock();Jobs.push(container);mJobMutex.unlock();}

		void RunThread();

		void Connect();
		bool Open(void) { if(hmp) return true; else return false;  }
		bool setupCache(int16 cacheResoulutionDivider);
		static inline bool isHeightmapCacheAvaliable(void) { return mCacheAvaliable;}
		inline bool isHighResCache(void) { return (mCacheResoulutionDivider == 1);}
		float getCachedHeightAt2DPosition(float xPos, float zPos) const;
		float getHeight(float x, float y);
	protected:
		Heightmap(const char* planet_name);
		~Heightmap();

	private:
		// This constructor prevents the default constructor to be used, since it is private.
		Heightmap();


		//DO NOT AND I REPEAT DO NOT USE THIS FOR ---ANYTHING---
		//EXCEPT FOR ONE TIME READS LIKE GETTING THE HEIGHT FOR
		//PLAYER BUILDING PLACEMENT!!!
		void fillInIterator(HeightResultMap::iterator it);

		//Dumps raw height variables. After recieving the data to get a proper height
		//value one must make sure the water bit is 0, cast to a float, then divide by 10.
		//see getHeight for an example how this is done.
		bool getRow(unsigned char* buffer, int32 x, int32 y, int32 length);

		//DO NOT AND I REPEAT DO NOT USE THIS FOR ---ANYTHING---
		//EXCEPT FOR ONE TIME READS LIKE GETTING THE HEIGHT FOR
		//PLAYER BUILDING PLACEMENT!!!

		const char* getFilename() const { return mFilename.c_str(); }

		void setFilename(std::string filename) { mFilename = filename; }

		unsigned long getOffset(float x, float y) const ;

		int32 round_coord(float coord) const;

		float	**mHeightmapCache;
		int32	mCacheHeight;
		int32	mCacheWidth;
		int16	mCacheResoulutionDivider;

		static bool	mCacheAvaliable;

		boost::thread			    mThread;
		bool						  mExit;

	protected:

		static Heightmap*  mInstance;
		// static bool        mInsFlag;
		std::string mFilename;
		FILE * hmp; //file pointer to the highmap

		int32		WIDTH;
		int32   HEIGHT;

		std::queue<HeightmapAsyncContainer*> Jobs;
		boost::mutex mJobMutex;
};

#endif
