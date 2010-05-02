/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_ZONESERVER_UIINPUTFIELD_H
#define ANH_ZONESERVER_UIINPUTFIELD_H

#include "Utils/typedefs.h"
#include "UIElement.h"

//================================================================================

class UIInputField : public UIElement
{
	public:

		UIInputField(){}
		UIInputField(uint32 id,BString name,bool enabled = true,uint16 maxLength = 127);
		virtual ~UIInputField();

		BString			getName(){ return mName; }
		void			setName(BString name){ mName = name; }

		bool			getEnabled(){ return mEnabled; }
		void			setEnabled(bool e){ mEnabled = e; }

		uint16			getMaxLength(){ return mMaxLength; }
		void			setMaxLength(uint16 maxLength){ mMaxLength = maxLength; }

		virtual uint32	getPropertyCount();

		virtual void	addMessageData();

	private:

		BString	mName;
		bool	mEnabled;
		uint16	mMaxLength;
};

#endif


