// Day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <algorithm>
std::vector<int> Data;

void GetInput(std::string FileData)
{
	std::fstream file(FileData, std::ios_base::in);
	size_t num = 0;
	while (file >> num)
	{
		Data.push_back(num);
	}

	file.close();
	std::sort(Data.begin(), Data.end());
}




int difference(int const jolts1, int const jolts2)
{
	int differenceCountNum1 = 1, differenceCountNum2 = 1;
	
	for (int i = 1; i < Data.size(); i++)
	{
		if (Data[i] - Data[i - 1] == jolts1)
			differenceCountNum1++;
		if (Data[i] - Data[i - 1] == jolts2)
			differenceCountNum2++;
	}
	return differenceCountNum1 * differenceCountNum2;
}

long long  arrangements2()
{
	std::vector<std::int64_t> arrangements;
	arrangements.resize(Data.back() + 3);
	arrangements[2] = 1;
	for (int i : Data) 
	{
		arrangements.at(i+2)= arrangements.at(i - 1) + arrangements[i] + arrangements[i + 1];
	}

	return arrangements[arrangements.size()-1];
} 
int main()
{

	GetInput("Day10Data.txt");
	std::cout << "Diffence Result of 1 jolt and 3 Jolt multiplied together is: " << difference(1, 3) << std::endl;
	std::cout << "The total number of distinct ways you can arrange the adapters to connect the charging outlet to your device: " << arrangements2() << std::endl; 
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
