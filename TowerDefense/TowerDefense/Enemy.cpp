#include "Enemy.h"


Enemy::Enemy(float x, float y)
	:MovableObject(x, y), m_health(100.0f), m_enemyNum(-1), fixedUpdateTimer(0)
{
	init();
}


Enemy::Enemy(sf::Vector2f pos)
	:MovableObject(pos), m_health(100.0f), m_enemyNum(-1), fixedUpdateTimer(0)
{
	init();
}
	
Enemy::~Enemy()
{
}

void Enemy::init()
{
	msprite = new sf::CircleShape(10.0f);
	msprite->setPosition(getPos());
	msprite->setOrigin(msprite->getGlobalBounds().width/2, msprite->getGlobalBounds().height/2);
}

int Enemy::GetEnemyNum() const
{
	return m_enemyNum;
}

int Enemy::GetHealth() const
{
	return m_health;
}

bool Enemy::IsDead() const
{
	return m_health < 0;
}

void Enemy::setEnemyNum(int num)
{
	m_enemyNum = num;
}

void Enemy::takeDamage(int dmg)
{
	std::cout << m_enemyNum << " is taking damage: " << dmg << std::endl;
	if(dmg > 100)
		std::cout << "There is a problem here" << std::endl;
	m_health -= dmg;
}

bool Enemy::operator==(const Enemy* other)
{
	if(this->m_enemyNum == other->GetEnemyNum() && this->m_health == other->GetHealth())
		return true; 
	return false;
}
