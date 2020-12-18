// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

enum class State : char
{
	empty = 'L',
	occupied = '#',
	unavailable = '.'
};

std::vector<std::string> Data;

void GetInput(std::string FileData)
{
	std::ifstream file(FileData);
	std::string line;

	while (std::getline(file, line))
	{
		Data.push_back(line);
	}

	file.close();
}

int CheckoccupiedOne(std::vector<std::string>& floor, int x, int y)
{
	//check around seat neightbors
	int count = 0;
	if (y > 0)
	{

		count += (static_cast<State>(floor[y - 1].at(x))== State::occupied);

		if (x > 0)
			count += (static_cast<State>(floor[y - 1].at(x - 1)) == State::occupied);
		if (x < floor[y].size() - 1)
			count += (static_cast<State>(floor[y - 1].at(x + 1)) == State::occupied);
	}
	if (y < floor.size() - 1)
	{
		count += (static_cast<State>(floor[y + 1].at(x)) == State::occupied);

		if (x > 0)
			count += (static_cast<State>(floor[y + 1].at(x - 1)) == State::occupied);
		if (x < floor[y].size() - 1)
			count += (static_cast<State>(floor[y + 1].at(x + 1)) == State::occupied);
	}

	if (x > 0)
		count += (static_cast<State>(floor[y].at(x - 1)) == State::occupied);
	if (x < floor[y].size() - 1)
		count += (static_cast<State>(floor[y].at(x + 1)) == State::occupied);

	return count;
}
int CheckoccupiedTwo(std::vector<std::string>& floor, int x, int y)
{
	size_t count = 0;
	long int i = y, j = x;
	// vertical directions first
	while (i > 0 && floor[--i][x] == '.');

	if (y > 0)
		count += (floor[i][x] == '#');
	i = y;



	while (i < floor.size() - 1 && floor[++i][x] == '.');

	if (y < floor.size() - 1)
		count += (floor[i][x] == '#');
	i = y;



	// horizontal directions
	while (j > 0 && floor[y][--j] == '.');

	if (x > 0)
		count += (floor[y][j] == '#');
	j = x;



	while (j < floor[y].size() - 1 && floor[y][++j] == '.');

	if (x < floor[y].size() - 1)
		count += (floor[y][j] == '#');
	j = x;



	while (i > 0 && j > 0 && floor[--i][--j] == '.');
	if (y > 0 && x > 0)
		count += (floor[i][j] == '#');
	i = y; j = x;



	while (i < floor.size() - 1 && j < floor[y].size() - 1 && floor[++i][++j] == '.');

	if (y < floor.size() - 1 && x < floor[y].size() - 1)
		count += (floor[i][j] == '#');

	i = y; j = x;


	// anti diagonal directions
	while (i < floor.size() - 1 && j > 0 && floor[++i][--j] == '.');

	if (y < floor.size() - 1 && x > 0)
		count += (floor[i][j] == '#');

	i = y; j = x;


	while (i > 0 && j < floor[y].size() - 1 && floor[--i][++j] == '.');

	if (y > 0 && x < floor[y].size() - 1)
		count += (floor[i][j] == '#');

	i = y; j = x;



	return count;
}


std::vector<std::string> NextData(std::vector<std::string>& current, const int limit , const bool OneORTwo)
{

	std::vector<std::string> NewData = current;
	for (size_t i = 0; i < NewData.size(); ++i)
	{
		for (size_t j= 0; j < NewData[i].size(); ++j)
		{
		if (static_cast<State>(current[i].at(j)) == State::unavailable)
				continue;

			int countSeated = 0;

			if(OneORTwo)
				countSeated = CheckoccupiedOne(current, j, i);
			else
				countSeated = CheckoccupiedTwo(current, j, i);

			if (static_cast<State>(current[i].at(j)) == State::empty && countSeated == 0)
				NewData[i][j] = '#';
			else if (static_cast<State>(current[i].at(j)) == State::occupied && countSeated >= limit)
				NewData[i][j] = 'L';

		}
	}
	return NewData;
}

int OccupiedSeats(const int limit, const bool OneORTwo)
{
	std::vector < std::string>  currentData = Data;
	std::vector < std::string> newData(currentData.size());
	bool different = true;
	while (different)
	{
		newData = NextData(currentData, limit, OneORTwo);
		different = false;
		for (int i = 0; i < Data.size(); ++i)
		{

			if (different = (currentData[i] != newData[i]))
				break;
		}
		currentData = newData;

	}

	int  count = std::accumulate(newData.begin(), newData.end(), 0,
		[](size_t sum, const std::string& sit) {
			return sum + std::count(sit.begin(), sit.end(), '#');
		});
	
	return count;

}


int main()
{
	GetInput("Day11Data.txt");
	std::cout <<" Seated filled part 1: " <<OccupiedSeats(4, true) << std::endl;
	std::cout << " Seated filled part 2: " << OccupiedSeats(5, false) << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
