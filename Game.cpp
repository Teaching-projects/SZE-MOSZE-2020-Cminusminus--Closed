﻿#include "Game.h"

Game::Game() {}

Game::Game(std::string mapfilename)
{
	Map map(mapfilename);
	setMap(map);
	maxColumns = map.getMaxCols();
}

void Game::setMap(Map map)
{
	if (heroPut || monsterPut)
	{
		throw AlreadyHasUnitsException("The units are already set up. Map cannot be changed.");
	}
	if (gameStarted)
	{
		throw GameAlreadyStartedException("Game already started!");
	}
	mapToSet = map;
	mapSet = true;
}

void Game::putHero(Hero hero, int x, int y)
{
	if (mapSet == false)
	{
		throw Map::WrongIndexException("No map initialized!");
	}
	if (mapToSet.get(x, y) == 1)
	{
		throw OccupiedException("There's a wall in this position!\n");
	}
	if (heroPut)
	{
		throw AlreadyHasHeroException("A hero has already been set!");
	}
	if (gameStarted)
	{
		throw GameAlreadyStartedException("The game has already started!");
	}

	heroPos = std::make_pair(x,y);
	mapHero = new Hero(hero);
	heroPut = true;
}

void Game::putMonster(Monster monster, int x, int y)
{
	if (mapSet == false)
	{
		throw Map::WrongIndexException("No map initialized!");
	}
	if (mapToSet.get(x, y) == 1)
	{
		throw OccupiedException("There's a wall in this position!");
	}
	if (monsterPut == false)
	{
		mapMonsters.push_back(std::make_pair(monster, std::make_pair(x, y)));
		monsterPut = true;
	}
	else
	{
		mapMonsters.push_back(std::make_pair(monster, std::make_pair(x, y)));
	}
}

void Game::run()
{

	if ((heroPut == false) || (mapSet == false))
	{
		throw NotInitializedException("The game is not initialized!");
	}

	std::string move;
	gameStarted = true;
	unsigned int deadMonsterCount = 0;

	while (mapMonsters.size() > deadMonsterCount && mapHero != nullptr)
	{
		for (int i = 0; i < mapMonsters.size(); i++)
		{
			if ((mapMonsters[i].second.first == heroPos.first) && (mapMonsters[i].second.second == heroPos.second))
			{
				mapHero->fightTilDeath(mapMonsters[i].first);
				if (mapMonsters[i].first.isAlive() == false)
				{
					deadMonsterCount++;
					if (deadMonsterCount == mapMonsters.size())
					{
						std::cout << mapHero->getName() << " cleared the map." << std::endl;
						break;
					}
				}
				else if(mapHero->isAlive() == false)
				{
					std::cout << "The hero died." << std::endl;
					heroPut = false;
					mapHero = nullptr;
				}

			}
		}
		if (mapHero == nullptr || mapMonsters.size() == deadMonsterCount)
		{
			gameStarted = false;
			break;
		}
		mapDraw();
		std::cin >> move;
		try
		{
			if (move == "north")
			{
				moveHero(heroPos.first - 1, heroPos.second);
			}
			if (move == "south")
			{
				moveHero(heroPos.first + 1, heroPos.second);
			}
			if (move == "west")
			{
				moveHero(heroPos.first, heroPos.second - 1);
			}
			if (move == "east")
			{
				moveHero(heroPos.first, heroPos.second + 1);
			}
		}
		catch (OccupiedException e)
		{
			std::cout << "There's a wall in this position!\n";
			continue;
		}
	}
}

void Game::mapDraw()
{
	std::cout << "╔";
	for (int i = 0; i < maxColumns; i++)
	{
		std::cout << "══";
	}
	std::cout << "╗\n";
	for (int i = 0; i < mapToSet.getRows(); i++)
	{
		std::cout << "║";
		for (int j = 0; j < mapToSet.getColumns(i); j++)
		{
			if (mapToSet.get(i, j) == 1)
			{
				std::cout << "██";
			}
			else if (heroPos.first == i && heroPos.second == j)
			{
				std::cout << "┣┫";
			}
			else if (monsterCount(i, j) == 1)
			{
				std::cout << "M░";
			}
			else if (monsterCount(i, j) > 1)
			{
				std::cout << "MM";
			}
			else
			{
				std::cout << "░░";
			}
		}
		for (int k = mapToSet.getColumns(i); k < maxColumns; k++)
		{
			std::cout << "██";
		}
		std::cout << "║\n";;
	}
	std::cout << "╚";
	for (int i = 0; i < maxColumns; i++)
	{
		std::cout << "══";
	}
	std::cout << "╝\n";
	std::cout << "To move the hero write north, south, west, or east" << std::endl;
}

int Game::monsterCount(int x, int y)
{
	int count = 0;
	for (int i = 0; i < mapMonsters.size(); i++)
	{
		if (mapMonsters[i].second.first == x && mapMonsters[i].second.second == y && mapMonsters[i].first.isAlive())
		{
			count++;
		}
	}
	return count;
}

void Game::moveHero(int x, int y)
{
	if (mapToSet.get(x, y) == 1) 
	{
		throw OccupiedException("There's a wall in this position!\n");
	}

	heroPos = std::make_pair(x, y);
}
