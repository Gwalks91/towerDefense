#pragma once

#include <SFML\Graphics.hpp>
#include "Defines.h"

class BaseObject
{
protected:
	sf::Vector2f m_pos;
public:
	sf::CircleShape* msprite;

	bool checkInWindow()
	{
		//This might need to be changed when the view moves
		if(m_pos.x < SCREEN_WIDTH && m_pos.x > 0 &&  m_pos.y < SCREEN_HEIGHT && m_pos.y > 0)
		{
			return true;
		}
		return false;
	}

	virtual ~BaseObject() { delete msprite; };
	virtual void update(float deltaTime) {};
	virtual void draw(sf::RenderWindow& window)
	{
		msprite->setPosition(m_pos);
		window.draw(*msprite);
	};


};