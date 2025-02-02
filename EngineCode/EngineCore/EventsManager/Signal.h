#pragma once

#include "Common/EngineObject.h"
#include "FastDelegate.h"

class Event;


typedef fastdelegate::FastDelegate2< const EngineObject*, Event* >		SignalDelegate;
typedef fastdelegate::FastDelegate2< const EngineObject*, Event* >		EventDelegate;




struct Signal
{
	const EngineObject*		Sender;
	const EngineObject*		Receiver;
	Event*					Parameters;		///< Event zawieraj�cy parametry wywo�ania.
	SignalDelegate			SignalHandler;	///< Delegat zawieraj�cy funkcj� obs�ugi sygna�u.
	SignalDelegate			OnExecuted;		///< Delegat wywo�ywany, gdy zako�czy si� obs�uga signa�u.
};


struct EventListener
{
	const EngineObject*		Receiver;
	EventDelegate			EventHandler;
};

