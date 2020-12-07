// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>


std::vector<std::vector<std::string>> Data;
void GetInput(std::string FileData)
{

	std::ifstream file(FileData);

	std::string line;
	std::vector<std::string> GroupQuestions;
	while (std::getline(file, line))
	{
		if (line.length() == 0)
		{
			Data.push_back(GroupQuestions);
			GroupQuestions.clear();
		}
		else
			GroupQuestions.push_back(line);

	}
	Data.push_back(GroupQuestions);

	file.close();

}


int SumPart1()
{
	int count = 0;
	for (auto group : Data)
	{
	
		bool questions[26] = {};
		for (auto person : group)
		{
			for (auto ch : person)
			{
				questions[ch - 'a'] = true;
			}
		}

		for (auto question : questions)
		{
			if (question)
				count++;

		}
	}
	return count;
}

int SumPart2()
{
	int count = 0;
	for (auto group : Data)
	{
		
		int questions[26] = {};
		for (auto person : group)
		{
			for (auto ch : person)
			{
				questions[ch - 'a']++;
			}
		}

		for (auto question : questions)
		{
			if (question == group.size())
				count++;
		}
	}
	return count;
}

int main()
{
	
	GetInput("Day6Data.txt");
	std:: cout <<"Sum of questions part 1: " <<SumPart1() << std::endl;
	std::cout << "Sum of questions part 2: " << SumPart2() << std::endl;
	system("Pause");
}