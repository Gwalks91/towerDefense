#pragma once

#include "MovableObject.h"

class MovableObject;

class Command
{
public:
	virtual ~Command() {};
	virtual void enter() {};
	virtual void execute(MovableObject* obj) = 0;
	virtual void exit() {};

};
