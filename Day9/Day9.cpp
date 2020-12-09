// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_set>

std::vector<int64_t> Data;

void GetInput(std::string FileData)
{
	std::fstream file(FileData, std::ios_base::in);
	int64_t num=0;
	while (file >> num)
	{
		Data.push_back(num);
	}
		
	file.close();
}

bool IsSumAPair(std::vector<int64_t> &previous, int64_t sum)
{

	std::unordered_set<int64_t> seenNum;
	for (auto num : previous) 
	{
		if (seenNum.count(sum - num))
			return true;
		seenNum.insert(num);
	}

	return false;
}

int FirstNumberNotASum(int64_t size)
{
	std::vector<int64_t> previousNum;
	int count = 0;
	for (auto num : Data) 
	{
		if (count < size)
			previousNum.push_back(num);
		else 
		{
			if(!IsSumAPair(previousNum, num))
				return num;
			previousNum.erase(previousNum.begin());
			previousNum.push_back(num);
		}
		count++;
	}
	return -1;

}
int main()
{
	GetInput("Test.txt");
	std::cout << "Test Data" << std::endl;
	std::cout << "First Number that is not a : " << FirstNumberNotASum(5) << std::endl;
	Data.clear();
	GetInput("Day9Data.txt");
	std::cout << "First Number that is not a : " << FirstNumberNotASum(25) << std::endl;
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
