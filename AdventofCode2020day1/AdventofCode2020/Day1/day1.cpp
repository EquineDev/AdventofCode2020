// AdventofCode2020day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map> 


std::unordered_map<int, int> umapData;

void ReadFile()
{
	std::ifstream file("dataDay1.txt");
	int num;
	while (file.eof() == false)
	{
		file >> num;
		umapData[num] = num;

	}
	file.close();

}

bool FindExpenseReportAnswerPartOne(int year)
{
	for (auto data : umapData)
	{
		int complement = year - data.second;
		if (umapData.find(complement) != umapData.end()) {
			std::cout << data.second << " & " << complement << " are a match! Answer is " << data.second * complement << std::endl;
			return true;
		}
	}
	return false;
}
bool FindExpenseReportAnswerPartTwo(int year)
{

	std::vector <int> numbers;

	for (const auto& s : umapData)
		numbers.push_back(s.second);

	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			for (int k = 0; k < j; ++k)
			{
				if (numbers[i] + numbers[j] + numbers[k] == year)
				{
					std::cout << numbers[i] << " & " << numbers[j] <<  " & "  << numbers[k] << " are a match! Answer is " << numbers[i] * numbers[j] * numbers[k] << std::endl;
					return true;
					
				}
			}
		}
	}

	return false;
}

	int main()
	{
		ReadFile();
		if (FindExpenseReportAnswerPartOne(2020) == false)
			std::cout << "No match found in data set in part one" << std::endl;
		else
			std::cout << "Match found in part one!" << std::endl;
		if (FindExpenseReportAnswerPartTwo(2020) == false)
			std::cout << "No match found in data set in part two" << std::endl;
		else
			std::cout << "Match found in part two!" << std::endl;
		system("Pause");
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
