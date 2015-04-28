#pragma once

#include <iostream>
#include <queue>
#include <set>
#include <random>

#include <SFML\Graphics.hpp>
#include "Defines.h"
#include "Command.h"
#include "MoveCommand.h"
#include "Enemy.h"
#include "SpawnerStruct.h"

enum MASKS
{
	TILENUM = 0X0F,
	WALKABLE = 0x10,
	BUILDABLE = 0x20
};

class SquareGrid
{
private:
	int mWidth, mHeight;
	int mTileWidth, mTileHeight;
	int endPos;
	
	uint8* mTiles;

	void LoadGrid(std::vector<SpawnerStruct>& enemySpawners);
	void addToFrontier(int current, int toAdd, std::queue<int>& fronter, std::set<int>& checked);

	void changeTile(int tileNum);
	
public:
	int startPos;
	int* mNeighbors;

	SquareGrid();
	~SquareGrid();
	bool init(/*std::string file*/ std::vector<SpawnerStruct>& enemySpawners);

	int getTileWidth();
	int getTileHeight();
	int getGridWidth();
	int getGridHeight();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	void BreadthFirst();

	sf::Vector2f getPosOfTile(int tileNum); // Gets the center of the tile
	sf::Vector2f getPosInTile(int tileNum); // Gets a random position that is inside the tile
	void CalculatePath(MovableObject* e);

	int checkClick(sf::Vector2i mouseClick);

};