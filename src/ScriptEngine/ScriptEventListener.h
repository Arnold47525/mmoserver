/*
---------------------------------------------------------------------------------------
This source file is part of swgANH (Star Wars Galaxies - A New Hope - Server Emulator)
For more information, see http://www.swganh.org


Copyright (c) 2006 - 2010 The swgANH Team

---------------------------------------------------------------------------------------
*/

#ifndef ANH_SCRIPT_EVENT_LISTENER_H
#define ANH_SCRIPT_EVENT_LISTENER_H

#include "Utils/typedefs.h"

#include <map>
#include <string>
#include <list>

class Script;

typedef std::list<Script*>					ScriptList;
typedef std::map<std::string, ScriptList*>	ScriptListMap;

//======================================================================================================================

class ScriptEventListener
{
	public:

		ScriptEventListener();
		~ScriptEventListener();

		void		registerFunction(const int8* functionName);
		void		unregisterFunction(const int8* functionName);

		void		registerScript(Script* script,const int8* functionName);
		void		unregisterScript(Script* script);

		void		handleScriptEvent(const int8* functionName,BString params);

		ScriptList*	getScriptList(const int8* functionName);

	private:

		void		_removeScriptList(const int8* functionName);

		ScriptListMap	mScriptListMap;
};

//======================================================================================================================

#endif


