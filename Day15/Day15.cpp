// Day15.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
const std::vector<int> Data{ 0,1,5,10,3,12,19 };

int countNumberth(int NumberNth)
{
    std::unordered_map<int, int> position;
    for(int i = 0;  i < Data.size()-1; i++)
    {
        position[Data[i]] = i;
    }

    int positionBack = Data.back(), positionBackNext = 0;
    auto iter = position.find(positionBack);
    for (int i = position.size(); i < NumberNth - 1; ++i) 
    {
        //std::cout << positionBack << "\n";
       
        
        if (position.end() != iter)
            positionBackNext = i - iter->second;

        position[positionBack] = i;
        positionBack = positionBackNext;
        //setup for next loop
        iter = position.find(positionBack);
        positionBackNext = 0;
    }

    return positionBack;
}

int main()
{

    std::cout <<"2020 Count: "<< countNumberth (2020)<<"\n";
    std::cout << "30000000 Count: " << countNumberth(30000000) << "\n";
 
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
