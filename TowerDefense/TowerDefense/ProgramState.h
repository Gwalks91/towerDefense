#pragma once

#include <iostream>

#include "SquareGrid.h"
#include "Spawner.h"
#include "Enemy.h"
#include "MouseExtra.h"

class ProgramState
{
protected:
	sf::RenderWindow* m_window;
public:
	virtual ~ProgramState() {};
	virtual void handleInput() {};
	virtual void update(float deltaTime) {};
	virtual void draw() {};
};