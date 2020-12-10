// Day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <algorithm>

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

int FindEncryptionWeakness(int numberToFind) 
{
	int nCount = Data.size();
	std::vector<int64_t> presum(nCount, 0);
	std::vector<int> location;
	int64_t maxNum = INT_MIN, minNum = INT_MAX;
	int  start = 0, end =0;
	presum[0] = Data[0];

	//setup pre sum of numbers to be check againsted our number to find found
	for (int i = 1; i < nCount; i++)
		presum[i] = presum[i - 1] + Data[i];

	

	//find the sum of two number locations and store it so we can find the min and max numbers
	for (int i = 1; i < nCount; i++) 
	{
		for(int j =0; j < i; j++ )
		{
			if ((presum[i] - presum[j]) == numberToFind) 
			{
				location.push_back(j);
				location.push_back(i);
				break;
			}
		}
	}


	//find the max and min numbers in our pairs 
	for(int i = location[0];  i <= location[1]; i++)
	{
		minNum = std::min(minNum, Data[i]);
		maxNum = std::max(maxNum, Data[i]);
	}

	return minNum + maxNum;
}
int main()
{
	int numberToFind = 0;
	GetInput("Test.txt");
	std::cout << "Test Data" << std::endl;
	numberToFind = FirstNumberNotASum(5);
	std::cout << "First Number that is not a sum : " << numberToFind << std::endl;
	std::cout << "Sum of Weakness Numbers is : " << FindEncryptionWeakness(numberToFind) << std::endl;
	Data.clear();

	GetInput("Day9Data.txt");
	std::cout << "Real Data" << std::endl;
	numberToFind = FirstNumberNotASum(25);
	std::cout << "First Number that is not a : " << numberToFind << std::endl;
	std::cout << "Sum of Weakness Numbers is : " << FindEncryptionWeakness(numberToFind) << std::endl;
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
