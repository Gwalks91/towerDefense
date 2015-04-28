#pragma once

#include "SquareGrid.h"

SquareGrid::SquareGrid()
{
	std::srand(std::time(NULL));
}

SquareGrid::~SquareGrid()
{
	delete[] mTiles;
	delete[] mNeighbors;
}
	
bool SquareGrid::init(/*std::string file*/ std::vector<SpawnerStruct>& enemySpawners)
{
	startPos = 0;
	mWidth = 10;
	mHeight = 10;
	mTileWidth = 125;
	mTileHeight = 65;
	mTiles = new uint8[mWidth* mHeight];
	mNeighbors = new int[mWidth* mHeight];
	LoadGrid(enemySpawners);
	BreadthFirst();
	return true;
}

int SquareGrid::getTileWidth()
{
	return mTileWidth;
}
	
int SquareGrid::getTileHeight()
{
	return mTileHeight;
}
	
int SquareGrid::getGridWidth()
{
	return mWidth;
}
	
int SquareGrid::getGridHeight()
{
	return mHeight;
}

void SquareGrid::update(float deltaTime)
{

}

void SquareGrid::draw(sf::RenderWindow& window)
{
	sf::RectangleShape temp(sf::Vector2f(mTileWidth, mTileHeight));
	temp.setPosition(0,0);
	temp.setOrigin(mTileWidth/2.0f, mTileHeight/2.0f);
	temp.setFillColor(sf::Color::White);
	//Need to check if the tile is in the window
	for(int i = 0; i < (mWidth* mHeight); i++)
	{
		temp.setFillColor(sf::Color::White);

		temp.setPosition(((i%mWidth)*mTileWidth)+(mTileWidth/2), ((i/mWidth)*mTileHeight)+(mTileHeight/2));

		if(((mTiles[i] & TILENUM) == 0))
		{
			temp.setFillColor(sf::Color::Green);
		}
		if(((mTiles[i] & TILENUM) == 1))
		{
			temp.setFillColor(sf::Color::Blue);
		}
		if(((mTiles[i] & TILENUM) == 2))
		{
			temp.setFillColor(sf::Color::Yellow);
		}
		if(((mTiles[i] & TILENUM) == 3))
		{
			temp.setFillColor(sf::Color::Red);
		}

		window.draw(temp);
	}
	//std::cout << std::endl;
}
	
void SquareGrid::BreadthFirst()
{
	std::queue<int> fronter = std::queue<int>();
	std::set<int> checked =std::set<int>();
	fronter.push(endPos);
	mNeighbors[endPos] = endPos;
	checked.insert(endPos);
	int current;

	while(!fronter.empty())
	{
		current = fronter.front();
		fronter.pop();	
		//Check to see if the node isnt in the first column
		if(current% mWidth != 0)
		{
			addToFrontier(current, current-1, fronter, checked);
		}
		//Check to see if the node isnt in the last col
		if(current % mWidth != mWidth -1)
		{
			addToFrontier(current, current+1, fronter, checked);
		}
		//Check to see if the node is in the first row
		if(current / mWidth != 0)
		{
			addToFrontier(current, current-mWidth, fronter, checked);			
		}
		//check to see if the node is in the last row
		if(current / mHeight != mHeight-1)
		{
			addToFrontier(current, current+mWidth, fronter, checked);		
		}

	}
}

void SquareGrid::LoadGrid(std::vector<SpawnerStruct>& enemySpawners)
{
	int temp [100] = {0, 3, 1, 0, 1, 1, 1, 1, 1, 1,
					1, 3, 1, 3, 1, 1, 1, 1, 1, 1,
					1, 3, 1, 1, 1, 3, 1, 1, 1, 1,
					1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
					1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
					1, 1, 1, 3, 3, 3, 1, 3, 1, 1,
					1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
					1, 3, 3, 1, 1, 1, 1, 3, 1, 1,
					1, 1, 1, 1, 1, 1, 1, 3, 1, 1,
					0, 1, 1, 1, 1, 1, 1, 3, 1, 2};

	for (int j = 0; j < (mWidth* mHeight); j++)
	{
		mNeighbors[j] = -1;
	}

	for(int i = 0; i < (mWidth* mHeight); i++)
	{
		uint8 t;
		switch (temp[i])
		{
		case 0:
			//Tile number plus walkable shifted over by 4 bits
			t = temp[i] + WALKABLE;
			mTiles[i] = t;
			SpawnerStruct s;
			s.spawner = new SpawnerFor<Enemy>();
			s.tileLocation = i;
			enemySpawners.push_back(s);
			break;
		case 1:
			t = temp[i] + WALKABLE + BUILDABLE;
			mTiles[i] = t;
			break;
		case 2: 
			t = temp[i] + WALKABLE;
			mTiles[i] = t;
			endPos = i;
			break;
		case 3:
			t = temp[i];
			mTiles[i] = t;
			endPos = i;
			break;
		}
	}
}

void SquareGrid::addToFrontier(int current, int toAdd, std::queue<int>& fronter, std::set<int>& checked)
{
	if(((mTiles[toAdd] & WALKABLE) != 0) && (checked.find(toAdd) == checked.end()))
	{
		fronter.push(toAdd);
		mNeighbors[toAdd] = current;
		checked.insert(toAdd);
	}
}

void SquareGrid::changeTile(int tileNum)
{
	mTiles[tileNum] = 3;
	BreadthFirst();
}

sf::Vector2f SquareGrid::getPosOfTile(int tileNum)
{
	return sf::Vector2f(((tileNum%mWidth)*mTileWidth)+(mTileWidth/2), ((tileNum/mWidth)*mTileHeight)+(mTileHeight/2));
}

sf::Vector2f SquareGrid::getPosInTile(int tileNum)
{
	sf::Vector2f temp;
	temp.x = (std::rand() % mTileWidth) + ((tileNum%mWidth)*mTileWidth);
	temp.y = (std::rand() % mTileHeight) + ((tileNum/mWidth)*mTileHeight);
	return temp;
}

void SquareGrid::CalculatePath(MovableObject* e)
{
	//Figure out start position of a passed in enemy
	int pos = ((int)e->getPos().x/mTileWidth) + ((int)e->getPos().y/mTileHeight)*mHeight;
	//std::cout << "Pos: " << e->getPos().x << ", " << e->getPos().y << std::endl;
	e->clearInput();
	//For each part of the path send a move command to the enemy
	while (pos != endPos)
	{
		//std::cout << "Path: " << pos << "->" << mNeighbors[pos] << std::endl;
		//Get the next part on the path and calculate what position to move to
		e->addInput(new MoveCommand((mNeighbors[pos]%mWidth)*mTileWidth + (mTileWidth/2), 
			(mNeighbors[pos]/mHeight)*mTileHeight+ (mTileHeight/2)));
		pos = mNeighbors[pos];
	}
}

//Gives the global 
int SquareGrid::checkClick(sf::Vector2i mouseClick)
{
	//check to see if the click was in the grid
	if(mouseClick.x > 0 && mouseClick.y > 0 && mouseClick.x < mWidth*mTileWidth && mouseClick.y < mHeight*mTileHeight)
	{
		changeTile((mouseClick.x/mTileWidth) + (mouseClick.y/mTileHeight)*mHeight);
		return (mouseClick.x/mTileWidth) + (mouseClick.y/mTileHeight)*mHeight;
	}
	return -1;
}