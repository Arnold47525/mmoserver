/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#include "ResourceType.h"


//=============================================================================

ResourceType::ResourceType()
{
}

//=============================================================================

ResourceType::~ResourceType()
{
}

//=============================================================================

BString ResourceType::getContainerModel()
{
	// gotta put shared_resource_container_ into the name
	BStringVector splits;
	BString tmpStr;
	tmpStr.setLength(512);

	int elements = mModel.split(splits,'/');

	tmpStr = splits[0].getAnsi();

	for(int i = 1;i < elements - 1;i++)
		tmpStr << "/" << splits[i].getAnsi(); 

	tmpStr << "/shared_resource_container_" << splits[elements-1].getAnsi();

return tmpStr;
}





