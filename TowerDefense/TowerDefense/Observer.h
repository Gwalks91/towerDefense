#pragma once

#include "Events.h"
#include "BaseObject.h"

class Observer
{
public: 
	virtual ~Observer() {};
	virtual void onNotify(const BaseObject& entity, Event event) = 0;
};