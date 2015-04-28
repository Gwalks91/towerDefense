#pragma once

#include "BaseObject.h"
#include "Trigger.h"
#include "Enemy.h"
#include <forward_list>

class BaseTower : public BaseObject, public Trigger
{
private:
	int m_dmg; 
	float m_coolDown, m_resetTime;
	sf::CircleShape m_range;

	Enemy* curEnemy;

	void init();

public:
	BaseTower(float x, float y);
	BaseTower(sf::Vector2f pos);
	virtual ~BaseTower();
	sf::Vector2f getPos();
	int getRadius();

	virtual void Exit(Enemy* obj);
	virtual void handleInput();
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
};