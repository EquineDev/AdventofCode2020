// Day4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Passport.h"

std::vector<Passport> Data; 
void GetInput(std::string FileData) {

	std::ifstream file(FileData);
	Passport passport;
	std::string line;

	while (std::getline(file, line)) {
		
		unsigned int index = 0;

		
		if (line == "") {
			Data.push_back(passport);
			passport.ClearFields();
		}

		
		while (index < line.size()) {
		

			//key name is only 3 chars long so 
			std::string fieldKey = line.substr(index, 3);
			index += 4;
			//value of the key find until we get a space
			std::string fieldValue = "";
			while (line[index] != ' ' && index < line.size()) {
				fieldValue += line[index];
				index++;
			}
			index++;
			passport.SetField(fieldKey, fieldValue);
		}
	}


	Data.push_back(passport);
	file.close();
}

int countValidPassports() {
	
	int validCount = 0;

	for (auto passport : Data) 
	{
		if (passport.isValid())
			validCount++;
	}
		
	return validCount;
}

int main()
{
	GetInput("Day4Data.txt");
	std::cout << "Here are the number of valid passports " << countValidPassports() << std::endl;
}
