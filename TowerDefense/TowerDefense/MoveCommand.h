#pragma once

#include "Command.h"

class MoveCommand : public Command
{
private:
	int mX, mY;

	MoveCommand();
public:
	MoveCommand(int x, int y);
	~MoveCommand();
	void enter();
	void execute(MovableObject* obj);
	void exit();
};