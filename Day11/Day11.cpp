// Day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

enum State
{
	empty,
	occupied,
	unavailable
};
std::unordered_map<char, State>  TokenTable = { {'L',State::empty}, {'#',State::occupied}, {'.',State::unavailable} };
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

int Checkoccupied(std::vector<std::string>& floor, int x, int y)
{
	//check around seat neightbors
	int count = 0;
	if (y > 0)
	{

		count += (TokenTable[floor[y - 1].at(x)] == State::occupied);

		if (x > 0)
			count += (TokenTable[floor[y - 1].at(x - 1)] == State::occupied);
		if (x < floor[y].size() - 1)
			count += (TokenTable[floor[y - 1].at(x + 1)] == State::occupied);
	}
	if (y < floor.size() - 1)
	{
		count += (TokenTable[floor[y + 1].at(x)] == State::occupied);

		if (x > 0)
			count += (TokenTable[floor[y + 1].at(x - 1)] == State::occupied);
		if (x < floor[y].size() - 1)
			count += (TokenTable[floor[y + 1].at(x + 1)] == State::occupied);
	}

	if (x > 0)
		count += (TokenTable[floor[y].at(x - 1)] == State::occupied);
	if (x < floor[y].size() - 1)
		count += (TokenTable[floor[y].at(x + 1)] == State::occupied);

	return count;
}
std::vector<std::string> NextData(std::vector<std::string>& current)
{

	std::vector<std::string> NewData = current;
	for (size_t i = 0; i < NewData.size(); ++i)
	{
		for (size_t j= 0; j < NewData[i].size(); ++j)
		{
		if (TokenTable[current[i].at(j)] == State::unavailable)
				continue;

			int countSeated = Checkoccupied(current, j, i);

			if (TokenTable[current[i].at(j)] == State::empty && countSeated == 0)
				NewData[i][j] = '#';
			else if (TokenTable[current[i].at(j)] == State::occupied && countSeated >= 4)
				NewData[i][j] = 'L';

		}
	}
	return NewData;
}

int OccupiedSeats()
{
	std::vector < std::string>  currentData = Data;
	std::vector < std::string> newData(currentData.size());
	bool different = true;
	while (different)
	{
		newData = NextData(currentData);
		different = false;
		for (int i = 0; i < Data.size(); ++i)
		{

			if (different = (currentData[i] != newData[i]))
				break;
		}
		currentData = newData;

	}

	int count = 0;
	for (int i = 0; i < newData.size(); ++i)
	{
		for (int j = 0; j < newData[i].size(); ++j)
		{
			if (TokenTable[newData[i].at(j)] == State::occupied)
				count++;

		}
	}
	
	return count;

}

int main()
{
	GetInput("Day11Data.txt");
	std::cout << OccupiedSeats();
	
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
