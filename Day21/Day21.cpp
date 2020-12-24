// Day21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm> 
#include <sstream> 
#include <string>
#include <set>
#include <map>
#include <vector> 

std::multiset<std::string> Appearances;
std::map<std::string, std::set<std::string>> Allergens;

void GetInput(std::string  filename)
{
	std::ifstream file(filename);
	std::string line;
	const auto aoffset = std::string{ "(contains " }.size();

	while (std::getline(file, line))
	{
		std::string ingredi, aller;
		auto pos = line.find('(');
		if ( pos != std::string::npos)
		{
			ingredi = line.substr(0, pos - 1);
			aller = line.substr((pos + aoffset), (line.size() - pos - aoffset - 1));
			aller.erase(remove(std::begin(aller), std::end(aller), ','), std::end(aller));
		}
		else 
		{
			ingredi = line;
		}

		std::set<std::string> ingredients;
		std::stringstream ss{ ingredi };
		std::string s;
		while (ss >> s) 
		{
			ingredients.insert(s);
			Appearances.insert(s);
		}
		ss = std::stringstream{ aller };
		while (ss >> s) 
		{
			auto [keyvalue, hasbeenNew] = Allergens.emplace(s, ingredients);
			if (!hasbeenNew)
			{
				std::set<std::string> intersect;
				std::set_intersection(
					begin(ingredients), end(ingredients),
					begin(keyvalue->second), end(keyvalue->second),
					inserter(intersect, begin(intersect)));
				keyvalue->second = move(intersect);
			}
		}

	
	}
	file.close();
}

int IngredientsCount()
{
	for (auto& keyvalue : Allergens) 
	{
		for (auto& al : keyvalue.second) 
		{
			Appearances.erase(al);
		}
	}
		
	return Appearances.size();
}

void DangerousIngredient()
{
	
	while (std::any_of(begin(Allergens), end(Allergens), [](auto& keyvalue) { return keyvalue.second.size() > 1; }))
	{
		for (auto& keyvalue : Allergens) 
		{

			if (keyvalue.second.size() == 1) 
			{
				std::string elem = *begin(keyvalue.second);

				for (auto& other : Allergens) 
				{
					if (keyvalue.first != other.first) 
						other.second.erase(elem);
				}
			}
		}
	}

	for (auto& keyvalue : Allergens)
	{
		std::cout << *begin(keyvalue.second) << ",";
	}
}
int main()
{
	GetInput("DataDay21.txt");
	std::cout << "Ingredients Count: " << IngredientsCount() <<"\n";
	DangerousIngredient();
    std::cout << "Hello World!\n";
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
