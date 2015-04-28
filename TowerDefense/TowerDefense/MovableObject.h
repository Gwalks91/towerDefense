#pragma once

#include <queue>

#include "BaseObject.h"
#include "Command.h"


class Command;

enum FLAGS
{
	moving = 0x01,
	dead = 0x02
};

class MovableObject : public BaseObject
{
private:
	uint8 flags;
	float maxSpeed;
	
	sf::Vector2f vel;
	sf::Vector2f currentTarget;
	std::queue<Command*> inputQueue; 

public:
	MovableObject(float x, float y);
	MovableObject(sf::Vector2f pos);
	virtual ~MovableObject();
	sf::Vector2f getPos();
	void moveTo(int x, int y);
	void addInput(Command* command);
	void clearInput();

	virtual void handleInput();

	virtual void update(float deltaTime);

	virtual void draw(sf::RenderWindow& window);
};