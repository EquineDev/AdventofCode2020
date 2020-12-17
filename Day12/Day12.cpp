// Day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

enum  class direction : std::uint8_t
{
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
	LEFT,
	RIGHT,
	FORWARD
};
struct instruction
{
	direction action;
	int value;
};


std::vector<instruction> Data;
std::unordered_map<char, direction>  TokenTable = { {'N',direction::NORTH}, {'S',direction::SOUTH}, {'E',direction::EAST}, {'W',direction::WEST}, {'L',direction::LEFT}, {'R',direction::RIGHT}, {'F',direction::FORWARD} };

void GetInput(std::string  filename)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		instruction data;
		data.action = TokenTable[line[0]];
		data.value = std::stoi(std::string(line.begin() + 1, line.end()));
		Data.push_back(data);
	}
	file.close();
}


void MoveShip(std::array<int, 2>& ship, const direction dir, int value)
{
	switch (dir)
	{
	case direction::NORTH:
		ship[1] += value;
		break;
	case direction::SOUTH:
		ship[1] -= value;
		break;
	case direction::EAST:
		ship[0] += value;
		break;
	case direction::WEST:
		ship[0] -= value;
		break;
	}
}

void MoveShip(std::array<int, 2>& ship, const instruction& dir)
{
	switch (dir.action)
	{
	case direction::NORTH:
		ship[1] += dir.value;
		break;
	case direction::EAST:
		ship[0] += dir.value;
		break;
	case direction::SOUTH:
		ship[1] -= dir.value;
		break;
	case direction::WEST:
		ship[0] -= dir.value;
		break;
	}
}

direction TurnLeft(direction dir, int degrees)
{

	int headingint = static_cast<int>(dir);
	headingint -= (degrees / 90);
	while (headingint < 0)
	{
		headingint += 4;
	}

	return static_cast<direction>(headingint);

}
std::array<int, 2> TurnLeft90(std::array<int, 2>& location)
{
	std::array<int, 2> newLoc;
	newLoc[0] = location[1];
	newLoc[1] = -location[0];
	return newLoc;
}

direction TurnRight(direction dir, int degrees)
{

	int headingint = static_cast<int>(dir);
	headingint += (degrees / 90);
	headingint %= 4;
	return static_cast<direction>(headingint);

}

std::array<int, 2> TurnRight90(std::array<int, 2>& location)
{
	std::array<int, 2> newLoc;
	newLoc[0] = -location[1];
	newLoc[1] = location[0];
	return newLoc;
}



void RunCourse(std::array<int, 2>& ship)
{
	direction dir = direction::EAST;
	for (auto instruction : Data)
	{
		switch (instruction.action)
		{
		case direction::FORWARD:
			MoveShip(ship, dir, instruction.value);
			break;
		case direction::LEFT:
			dir = TurnLeft(dir, instruction.value);
			break;
		case direction::RIGHT:
			dir = TurnRight(dir, instruction.value);
			break;
		default:
			MoveShip(ship, instruction);
			break;
		}


	}
}

void RunCourseWayPoints(std::array<int, 2>& ship)
{
	std::array<int, 2> cords = ship;
	ship = { 0, 0 };
	for (auto instruction : Data)
	{
		switch (instruction.action)
		{

		case direction::NORTH:
			cords[1] += instruction.value;
			break;
		case direction::EAST:
			cords[0] += instruction.value;
			break;
		case direction::SOUTH:
			cords[1] -= instruction.value;
			break;
		case direction::WEST:
			cords[0] -= instruction.value;
			break;
		case direction::FORWARD:

			ship[0] += instruction.value * cords[0];
			ship[1] += instruction.value * cords[1];
			std::cout << "MOVING " << instruction.value << "ship is at (" << ship[0] << ", " << ship[1]
				<< ") \n";
			break;
		case direction::LEFT:

			for (int i = 0; i < ((instruction.value / 90) % 4); ++i)
			{
				cords = TurnLeft90(cords);
			}

			break;
		case direction::RIGHT:

			for (int i = 0; i < ((instruction.value / 90) % 4); ++i)
			{
				cords = TurnRight90(cords);
			}
			break;
		}
		std::cout << "The waypoints is at (" << cords[0] << ", " << cords[1]
			<< ") \n";

	}
}

int main()
{
	std::array<int, 2> Ship = { 0,0 };
	GetInput("Day12Data.txt");
	RunCourse(Ship);
	std::cout << "The ship is at (" << Ship[0] << ", " << Ship[1]
		<< ") = " << std::abs(Ship[0]) + std::abs(Ship[1]) << "\n";
	Ship = { 10,1 };
	RunCourseWayPoints(Ship);
	std::cout << "The ship using waypoints is at (" << Ship[0] << ", " << Ship[1]
		<< ") = " << std::abs(Ship[0]) + std::abs(Ship[1]) << "\n";
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
