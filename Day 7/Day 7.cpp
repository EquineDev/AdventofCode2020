// Day 7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <map>

std::map<std::string, std::map<std::string, int>> Data;


bool CheckInBag(std::string color) 
{

	if (Data.at(color).count("shiny gold"))
		return true;

	return std::any_of(Data.at(color).begin(), Data.at(color).end(), [&](const std::pair<std::string, int>& rr) {
		return CheckInBag(rr.first);
		});
}

int NumbersInbag(std::string color) 
{
	return std::accumulate(Data.at(color).begin(), Data.at(color).end(), 1,
		[&](int sum, const std::pair<std::string, int>& rr) {
		return sum + rr.second * NumbersInbag(rr.first);
		});
}

std::map<std::string, int> CreateRule(std::vector<std::string> words)
{
	std::map<std::string, int> rule;
	for (int i = 0; i < words.size() / 4 - 1; ++i)
	{
		int quantity = std::stoi(words[4 * (i + 1)]);
		std::string in_col = words[4 * (i + 1) + 1] + " " + words[4 * (i + 1) + 2];
		rule[in_col] = quantity;
	}

	return rule;
}

int DayOneBagCheck()
{
	int count = 0;
	for (const auto& rule : Data)
	{
		if (CheckInBag(rule.first))
			count++;
	}
	return count;
}

int DayTwoBagCheck()
{
	
	return NumbersInbag("shiny gold") -1;
}



void GetInput(std::string FileData)
{
	std::ifstream file(FileData);

	std::string line;
	while (std::getline(file, line))
	{
		//clean up lines 
		line.erase(std::prev(line.end()));
		std::replace(line.begin(), line.end(), ',', ' ');

		std::stringstream stringLine(line);
		std::vector<std::string> words;
		std::string word;
		while (stringLine >> word)
		{
			words.push_back(word);
		}


		std::string color = words[0] + " " + words[1];
		std::map<std::string, int> rule = CreateRule(words);
		Data[color] = std::move(rule);
	}
}


int main()
{

	GetInput("Day7Data.txt");
	std::cout << "Sum of questions part 1: " << DayOneBagCheck() << std::endl;
	std::cout << "Sum of questions part 2: " << DayTwoBagCheck() << std::endl;
	system("Pause");
}


