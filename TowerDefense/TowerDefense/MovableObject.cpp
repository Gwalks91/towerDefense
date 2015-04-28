#include "MovableObject.h"

MovableObject::MovableObject(float x, float y)
	:flags(0), vel(0,0), maxSpeed(100.0f)
{
	m_pos = sf::Vector2f(x,y);
}
	
MovableObject::MovableObject(sf::Vector2f pos)
	:flags(0), vel(0,0), maxSpeed(100.0f)
{
	m_pos = sf::Vector2f(pos);
}
	
MovableObject::~MovableObject()
{
	while(!inputQueue.empty())
	{
		delete inputQueue.front();
		inputQueue.pop();
	}
}
	
sf::Vector2f MovableObject::getPos()
{
	return m_pos;
}

void MovableObject::moveTo(int x, int y)
{
	currentTarget.x = x;
	currentTarget.y = y;

	//Testing data to see how fast this happens
	float scaler = std::abs(x - m_pos.x) + std::abs(y - m_pos.y);
	vel.x = (x - m_pos.x)/scaler * maxSpeed;
	vel.y = (y - m_pos.y)/scaler * maxSpeed;

	flags += FLAGS::moving;
}

void MovableObject::addInput(Command* command)
{
	inputQueue.push(command);
}

void MovableObject::clearInput()
{
	while(!inputQueue.empty())
	{
		delete inputQueue.front();
		inputQueue.pop();
	}
	vel.x = 0;
	vel.y = 0;
	flags = 0;
}

void MovableObject::handleInput()
{
	if (((flags & FLAGS::moving) == 0) && !inputQueue.empty())
	{
		inputQueue.front()->execute(this);
		delete inputQueue.front();
		inputQueue.pop();
	}
}

void MovableObject::update(float deltaTime)
{
	m_pos.x += vel.x * deltaTime;
	m_pos.y += vel.y * deltaTime;

	//Check if the movable object is close to the desired position so it can start looking for the next position to move to
	if(m_pos.x > currentTarget.x - 1 && m_pos.x < currentTarget.x + 1 && 
		m_pos.y < currentTarget.y + 1 && m_pos.y > currentTarget.y - 1)
	{
		flags -= FLAGS::moving;
		vel.x = 0;
		vel.y = 0;
		m_pos = currentTarget;
	}
}

void MovableObject::draw(sf::RenderWindow& window)
{
	if(checkInWindow())
	{
		BaseObject::draw(window);
	}
}