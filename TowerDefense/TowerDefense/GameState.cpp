
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	:grid(), enemySpawners(), enemies(), numEnemies(5), towers(), fixedUpdateTimer(0)
{
	m_window = window;
	// Initialize the view to a rectangle located at (100, 100) and with a size of 400x200
	m_view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	// Set its target viewport to be half of the window
	m_view.setViewport(sf::FloatRect(0.f, 0.f, 1.0f, 1.f));
	// Apply it
	window->setView(m_view);

	grid.init(enemySpawners);
	spawnEnemies();
}
	
	
GameState::~GameState()
{
	while(!enemySpawners.empty())
	{
		delete enemySpawners.back().spawner;
		enemySpawners.pop_back();
	}
	while(!enemies.empty())
	{
		delete enemies.front();
		enemies.pop_front();
	}
	while(!towers.empty())
	{
		delete towers.back();
		towers.pop_back();
	}

	m_window = NULL;
}

void GameState::spawnEnemies()
{
	int numOfEnemies = 0;
	for(std::vector<SpawnerStruct>::iterator it = enemySpawners.begin(); it != enemySpawners.end(); it++)
	{
		for(int num = 0; num < numEnemies; num++)
		{
			enemies.push_front(it->spawner->spawnObject(grid.getPosInTile(it->tileLocation)));
			enemies.front()->setEnemyNum(numOfEnemies);
			grid.CalculatePath(enemies.front());
			numOfEnemies++;
		}
	}
}

void GameState::CheckInRange(BaseTower* tower, Enemy* enemy)
{
	bool temp = tower->CheckInList(enemy);
	if(std::pow(tower->getRadius(), 2) 
		>= (std::pow((enemy->getPos().x - tower->getPos().x),2) + std::pow((enemy->getPos().y - tower->getPos().y),2)))
	{
		if(!temp)
			tower->Enter(enemy);
	}
	else 
	{
		if(temp)
			tower->Exit(enemy);
	}
}

void GameState::handleInput()
{
	for(std::forward_list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->handleInput();
	}

	//This is will need to be moved to an inputhandler
	if (sf::MouseExtra::isButtonReleased(sf::Mouse::Left))
	{
		//Check to see if the click is outside the window
		if(sf::Mouse::getPosition(*m_window).x > 0 && sf::Mouse::getPosition(*m_window).y > 0
			&& sf::Mouse::getPosition(*m_window).x < SCREEN_WIDTH && sf::Mouse::getPosition(*m_window).y < SCREEN_HEIGHT)
		{
			int tile = grid.checkClick(sf::Mouse::getPosition(*m_window)+sf::Vector2i(m_view.getCenter().x-m_view.getSize().x/2, 
				m_view.getCenter().y-m_view.getSize().y/2));
			if(tile != -1)
			{
				towers.push_back(new BaseTower(grid.getPosOfTile(tile)));
				for(std::forward_list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
				{
					grid.CalculatePath(*it);
				}
			}

		}
		//grid.checkClick(localPosition);
		//std::cout << "Mouse Pos Local: " << localPosition.x << ", " << localPosition.y << std::endl; 
	}
	if (sf::MouseExtra::isButtonReleased(sf::Mouse::Right))
	{
		m_view.setCenter(m_view.getCenter().x + 10, m_view.getCenter().y);
		m_window->setView(m_view);
	}
}

void GameState::update(float deltaTime)
{
	for(std::forward_list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->update(deltaTime);
		if(fixedUpdateTimer % 3 == 2)
		{
			for(std::vector<BaseTower*>::iterator tower = towers.begin(); tower != towers.end(); tower++)
			{
				CheckInRange(*tower, *it);
			}
		}
		//This is not a good way to do this because it will stop the update early
		if((*it)->IsDead())
		{
			Enemy* temp = *it;
			std::cout << "Enemy: " << temp->GetEnemyNum() << " is dead!" << std::endl;
			enemies.remove(*it);
			delete temp;
			break;
		}
	}
	for(std::vector<BaseTower*>::iterator tower = towers.begin(); tower != towers.end(); tower++)
	{
		(*tower)->update(deltaTime);
	}
	if(fixedUpdateTimer % 3 == 2)
		fixedUpdateTimer = 0;
	else
		fixedUpdateTimer++;
}

void GameState::draw()
{
	grid.draw(*m_window);
	for(std::forward_list<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
	{
		(*it)->draw(*m_window);
	}
	for(std::vector<BaseTower*>::iterator it = towers.begin(); it != towers.end(); it++)
	{
		(*it)->draw(*m_window);
	}
}
