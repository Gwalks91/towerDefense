#pragma once

#include "ProgramState.h"
#include "SpawnerStruct.h"
#include "BaseTower.h"

class GameState : public ProgramState
{
private:
	int fixedUpdateTimer;
	float spawn_Timer, numEnemies;
	SquareGrid grid;
	sf::View m_view;
	std::vector<SpawnerStruct> enemySpawners;
	std::forward_list<Enemy*> enemies;
	std::vector<BaseTower*> towers;

	void spawnEnemies();
	void CheckInRange(BaseTower* tower, Enemy* enemy);
	GameState();
public: 
	GameState(sf::RenderWindow* window);
	virtual ~GameState();
	virtual void handleInput();
	virtual void update(float deltaTime);
	virtual void draw();



};
