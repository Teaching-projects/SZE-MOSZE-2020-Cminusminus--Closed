#include "MarkedMap.h"

MarkedMap::MarkedMap(std::string filename)
{
	std::ifstream ifst;
	std::string line;
	try
	{
		ifst.open(filename);
	}
	catch (const std::exception& e)
	{
		throw e.what();
	}

	while (!ifst.eof() && ifst.is_open())
	{
		std::getline(ifst, line);
		markedmap.push_back(line);
	}
	ifst.close();
}

Map::type MarkedMap::get(int x, int y) const
{
	if (x < 0 || x >= (int)markedmap.size())
	{
		throw WrongIndexException("Wrong index!");
	}
	else if (y < 0 || y >= (int)markedmap[x].length())
	{
		throw WrongIndexException("Wrong index!");
	}

	std::string types = " #";
	return type(types.find(markedmap[x][y]));
}

std::pair<int, int> MarkedMap::getHeroPosition() const
{
	for (int i = 0; i < markedmap.size(); i++)
	{
		for (int j = 0; j < markedmap[i].length(); j++)
		{

			if (markedmap[i][j] == 'H')
			{
				return std::make_pair(i, j);
			}
		}
	}
	
	return std::make_pair(-1, -1);
}

std::list<std::pair<int, int>> MarkedMap::getMonsterPosition(char c) const
{
	char type = c;
	std::list <std::pair<int, int>> templist;

	for (int i = 0; i < markedmap.size(); i++)
	{
		for (int j = 0; j < markedmap[i].length(); j++)
		{
			if (markedmap[i][j] == type)
			{

				templist.push_back(std::make_pair(i, j));
			}
		}
	}
	return templist;
	
}
