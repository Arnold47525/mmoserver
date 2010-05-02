/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_UIINPUTBOX_H
#define ANH_ZONESERVER_UIINPUTBOX_H

#include "Utils/typedefs.h"
#include "UIWindow.h"


//================================================================================

class UIInputBox : public UIWindow
{
	public:

		UIInputBox(UICallback* callback,uint32 id,uint8 windowType, const int8* eventStr,const int8* caption,const int8* text,const BStringVector dropdownElements
				  ,PlayerObject* playerObject,uint8 ibType = SUI_IB_NODROPDOWN_OKCANCEL,uint16 maxInputLength = 127);

		virtual ~UIInputBox();

		virtual	 void	handleEvent(Message* message);
		void			sendCreate();

	protected:

		void	_initChildren(BStringVector dropdownElements);

		BString			mCaption;
		BString			mPrompt;
		uint8			mIbType;
		uint16			mMaxInputLength;
};

//================================================================================

#endif




