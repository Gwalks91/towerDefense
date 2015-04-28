#pragma once

#include <iostream>

#include "MovableObject.h"
#include "Command.h"


class Enemy : public MovableObject
{
private:
	int m_enemyNum, m_health;
	int fixedUpdateTimer;

	Enemy();
	void init();
	void move();
	
public:
	Enemy(float x, float y);
	Enemy(sf::Vector2f pos);
	virtual ~Enemy();

	int GetEnemyNum() const;
	int GetHealth() const;
	bool IsDead() const;

	void setEnemyNum(int num);

	void takeDamage(int dmg);

	bool operator==(const Enemy* other);

};
