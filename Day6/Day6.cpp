// Day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

std::vector<std::vector<std::string>> data;
void GetInput(std::string FileData)
{

    std::ifstream file(FileData);
    std::string line;
    std::vector<std::string> group;
    while (std::getline(file, line))
    {
        if (line.length() == 0)
        {
            group.push_back(line);
            data.clear();
        }
        else
            group.push_back(line);
       
       
    }
    data.push_back(group);
    file.close();
}

int AnyQuestionSum() 
{
    int count = 0;
    std::unordered_set<char> answers;

    for (auto group : data) 
    {
        for (auto line : group) 
        {

            answers.insert(line.begin(), line.end());
        }
        count += answers.size();
        answers.clear();
    }
    return count; 
}

int main()
{
    GetInput("Day6Data.txt");
    std::cout << "Number of anwser is : " << AnyQuestionSum() << std::endl;
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
