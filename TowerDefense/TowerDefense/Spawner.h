#pragma once

#include "MovableObject.h"

class Spawner
{
public: 
	virtual ~Spawner() {};
	virtual Enemy* spawnObject(sf::Vector2f pos) = 0;
	virtual Enemy* spawnObject(float x, float y) = 0;

};

template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual Enemy* spawnObject(sf::Vector2f pos) { return new T(pos); }
	virtual Enemy* spawnObject(float x, float y) { return new T(x, y); }
};