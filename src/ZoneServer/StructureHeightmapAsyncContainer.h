#include "HeightmapAsyncContainer.h"

class StructureHeightmapAsyncContainer: public HeightmapAsyncContainer
{
public:
	StructureHeightmapAsyncContainer(HeightMapCallBack* callback, HeightmapCallbackTypes type) : HeightmapAsyncContainer(callback, type)
	{
	}
	
	ObjectFactory*	oCallback;
	ObjectFactoryCallback* ofCallback;
	Deed* deed;
	float x;
	float z;
	float dir; 
	BString customName;
	PlayerObject* player;
};
