#include "BaseTower.h"


BaseTower::BaseTower(float x, float y)
	:Trigger(), m_dmg(30), m_range(200), m_coolDown(1), m_resetTime(1), curEnemy(NULL)
{
	this->Trigger::Trigger();
	m_pos = sf::Vector2f(x,y);
	m_range.setPosition(x,y);
	m_range.setOrigin(m_range.getGlobalBounds().width/2, m_range.getGlobalBounds().height/2);
	init();
}
	
BaseTower::BaseTower(sf::Vector2f pos)
	:Trigger(), m_dmg(30), m_range(200), m_coolDown(1), m_resetTime(1), curEnemy(NULL)
{
	m_pos = sf::Vector2f(pos);
	m_range.setPosition(pos);
	m_range.setOrigin(m_range.getGlobalBounds().width/2, m_range.getGlobalBounds().height/2);
	init();
}

void BaseTower::init()
{
	m_range.setFillColor(sf::Color::Green);

	msprite = new sf::CircleShape(25.0f);
	msprite->setPosition(getPos());
	msprite->setOrigin(msprite->getGlobalBounds().width/2, msprite->getGlobalBounds().height/2);
}
	
BaseTower::~BaseTower()
{
}
	
sf::Vector2f BaseTower::getPos()
{
	return m_pos;
}
	
int BaseTower::getRadius()
{
	return m_range.getRadius();
}

void BaseTower::Exit(Enemy* obj)
{
	this->Trigger::Exit(obj);
	if(!m_inTrigList.empty())
	{
		curEnemy = m_inTrigList.front();
		m_coolDown = m_resetTime;
	}
	else 
		curEnemy = NULL;
}

void BaseTower::handleInput()
{

}
	
void BaseTower::update(float deltaTime)
{
	if(curEnemy != NULL)
	{
		m_coolDown -= deltaTime;
		if(m_coolDown < 0)
		{
			if(curEnemy->GetEnemyNum() > 100)
			{
				std::cout << "This is a problem!" << std::endl;
			}
			//Shoot enemy
			if(!curEnemy->IsDead())
			{
				curEnemy->takeDamage(m_dmg);
				m_coolDown = m_resetTime;
			}
			//Check to see if the current enemy is dead 
			//Should probably make gamestate and observer of the towers and send an update if tower kills one
			else
				Exit(curEnemy);
		}
	}
	else
	{
		if(!m_inTrigList.empty())
		{
			curEnemy = m_inTrigList.front();
			m_coolDown = m_resetTime;
		}
	}
}
	
void BaseTower::draw(sf::RenderWindow& window)
{
	if(checkInWindow())
	{
		//window.draw(m_range);
		BaseObject::draw(window);
	}
}