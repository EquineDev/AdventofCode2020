// Day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> data;
void GetInput(std::string FileData)
{
	std::ifstream file(FileData);
	std::string slopes;
	while (std::getline(file, slopes)) 
	{
		data.push_back(slopes);
	}
	file.close();

	
}

int FindTrees(int right, int down) 
{
	int treecount = 0, location = 0, row = 0;

	for (auto slope : data) 
	{
		location = (location + right) % slope.length();
		row += down;
		if (row >= data.size())
			return treecount;
		if (data[row][location] == '#')
			treecount++;
	}
	
	return treecount;
}



int main()
{
	GetInput("Day3Data.txt");
	std::cout << "This is how many trees we hit on slope 1: " <<FindTrees(3, 1) << std::endl;
	std::cout << "This is how many trees we hit on slope 2: " << FindTrees(1, 1) * FindTrees(3, 1) * FindTrees(5, 1)* FindTrees(7, 1) * FindTrees(1, 2) << std::endl;
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
