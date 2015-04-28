#pragma once 

#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> m_observers;
	int numObservers;

public:
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
};