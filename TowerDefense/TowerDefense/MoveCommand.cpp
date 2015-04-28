#include "MoveCommand.h"

MoveCommand::MoveCommand(int x, int y)
	:mX(x), mY(y)
{
}

	
MoveCommand::~MoveCommand()
{
}
	
void MoveCommand::enter()
{
}

void MoveCommand::execute(MovableObject* obj)
{
	obj->moveTo(mX, mY);
}
	
void MoveCommand::exit()
{

}