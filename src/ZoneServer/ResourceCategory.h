/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_RESOURCECATEGORY_H
#define ANH_ZONESERVER_RESOURCECATEGORY_H

#include "Utils/typedefs.h"
#include <list>

//=============================================================================

class Resource;
class ResourceCategory;

typedef std::list<ResourceCategory*>	ResourceCategoryList;
typedef std::list<Resource*>			ResourceList;

//=============================================================================

class ResourceCategory
{
	friend class ResourceManager;

	public:

		ResourceCategory();
		~ResourceCategory();

		uint32					getId(){ return mId; }
		void					setId(uint32 id){ mId = id; }
		uint32					getParentId(){ return mParentId; }
		void					setParentId(uint32 id){ mParentId = id; }
		ResourceCategoryList*	getChildren(){ return &mChildren; }
		ResourceList*			getSiblings(){ return &mSiblings; }
		BString					getName(){ return mName; }
		void					setName(const BString name){ mName = name; }
		BString					getDescriptor(){ return mDescriptor; }
		void					setDescriptor(const BString desc){ mDescriptor = desc; }
		void					insertCategory(ResourceCategory* cat){ mChildren.push_back(cat); }
		void					insertResource(Resource* res){ mSiblings.push_back(res); }
		void					getResources(ResourceList& resourceList,bool currentOnly);

	private:

		uint32					mId;
		uint32					mParentId;
		BString					mName;
		BString					mDescriptor;
		ResourceCategoryList	mChildren;
		ResourceList			mSiblings;
};

//=============================================================================

#endif

