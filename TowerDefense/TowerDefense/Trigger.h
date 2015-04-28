#pragma once

#include <list>
#include "Enemy.h"

class Trigger
{
public:
	Trigger()
		:m_inTrigList()
	{};
	virtual ~Trigger() 
	{
		m_inTrigList.clear();
	};
	virtual void Enter(Enemy* obj)
	{
		if(obj->GetEnemyNum() > 100)
		{
			std::cout << "This is a problem!" << std::endl;
		}
		m_inTrigList.push_back(obj);
	};

	virtual void Exit(Enemy* obj)
	{
		for(std::vector<Enemy*>::iterator enemy = m_inTrigList.begin(); enemy != m_inTrigList.end(); enemy++)
		{
			if(*enemy == obj)
			{
				m_inTrigList.erase(enemy);
				break;
			}
		}
	};

	bool CheckInList(Enemy* e)
	{
		if(m_inTrigList.empty())
			return false;
		for(std::vector<Enemy*>::iterator enemy = m_inTrigList.begin(); enemy != m_inTrigList.end(); enemy++)
		{
			if(*enemy == e)
				return true;
		}
		return false;
	};
protected:
	std::vector<Enemy*> m_inTrigList;

};