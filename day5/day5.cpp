// day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::vector<std::string> seats;
void GetInput(std::string FileData) 
{

    std::ifstream file(FileData);
    std::string line;

    while(std::getline(file, line))
    {
        seats.push_back(line);
    }
    file.close();
}

int IdSeat(std::string seat) 
{
    int xMin = 0, xMax = 7, yMin = 0, yMax = 127;
    for (int i = 0; i <= 6; i++) 
    {
        if ( seat[i] == 'F')
            yMax -= (yMax - yMin + 1) / 2;
        else if (seat[i] == 'B')
            yMin += (yMax - yMin + 1) / 2;
    }

    for (int i = 7; i <= 9; i++) 
    {
        if (seat[i] == 'L')
            xMax -= (xMax - xMin + 1) / 2;
        else if (seat[i] == 'R')
            xMin += (xMax - xMin + 1) / 2;
    }

    return yMin * 8 + xMin;
}


int HighSeatId() 
{
    int id = 0, test =0;
    for (auto seat : seats) 
    {
        test = IdSeat(seat);
            if (test > id)
                id = test;
    }
    return id;
}

int MissingSeatID()
{
    bool ids[1024] = {}; // there are 128*8=1024 possible seats

    for (std::string seat : seats)
    {
        int id = IdSeat(seat);
        ids[id] = true;
    }

    for (int i = 1; i < 1023; i++)
    {
        if (ids[i - 1] && !ids[i] && ids[i + 1])
        {
            return i;
        }
    }

    return -1;
}


int main()
{
    GetInput("Day5Data.txt");
    std::cout << "Here is the highest seat ID: " << HighSeatId() << std::endl;
    std::cout << "Here is the Missing seat ID: " << MissingSeatID() << std::endl;
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
