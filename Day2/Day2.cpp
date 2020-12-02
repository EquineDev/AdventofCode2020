// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int, int, char, std::string>> data;

void GetInput(std::string FileData)
{
    std::ifstream file(FileData);

    while (file.eof() == false)
    {
        int num1, num2;
        char dash, colon, letter;
        std::string pw;
        file >> num1 >> dash >> num2 >> letter >> colon >> pw;
        data.push_back(std::make_tuple(num1, num2, letter, pw));
    }
    file.close();

}

int NumberOfValidPasswordSetOne() 
{
    int valid = 0;

    for (auto password : data) 
    {
        int min, max, count =0;
        char letter;
        std::string pw;

        std::tie(min, max, letter, pw) = password;

        for (char c : pw) 
        {
            if (c == letter)
            {
                count++;
            }
        }
        if (min <= count && count <= max)
        {
            valid++;
        }
    }

    return valid;
}

int NumberOfValidPasswordSetTwo()
{
    int valid = 0;

    for (auto password : data)
    {
        int location1, location2;
        char letter;
        std::string pw;

        std::tie(location1, location2, letter, pw) = password;

        if ((pw[location1 - 1] == letter) != (pw[location2 - 1] == letter))
        {
            valid++;
        }
    }

    return valid;
}

int main()
{
    GetInput("DataDay2.txt");
    std::cout << "Number of Valid Password for Set One: " << NumberOfValidPasswordSetOne() << std::endl;
    std::cout << "Number of Valid Password For Set Two: " << NumberOfValidPasswordSetTwo() << std::endl;
    system("Pause");
}

