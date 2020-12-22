// Day16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <regex>
#include <Tuple>
#include <algorithm>
#include <sstream> 
#include <cassert>

std::unordered_map<std::string, std::tuple<long long, long long, long long, long long>> rules;
std::vector<long long> MyTicket;
std::vector<std::vector<long long>> GoodTickets;

bool valid(const std::string& rule, long long val)
{
	std::tuple<long long, long long, long long, long long > r = rules[rule];
	return (val >= std::get<0>(r) && val <= std::get<1>(r)) || (val >= std::get<2>(r) && val <= std::get<3>(r));
}

std::vector<long long> parseTicket(std::string& line)
{
	std::vector<long long> ticket;
	std::stringstream ss{ line };
	std::string s;
	while (getline(ss, s, ',')) 
	{ 
		ticket.push_back(stoll(s)); 
	}
	return ticket;
}

void GetInput(std::string  filename)
{
	std::regex rule_pattern{ R"((.*): (\d+)-(\d+) or (\d+)-(\d+))" };
	std::ifstream file(filename);
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty()) 
			break; 
		std::smatch match;
		if (!regex_match(line, match, rule_pattern))  
			assert(false); 

		rules[match[1]] = std::make_tuple(stoll(match[2]), stoll(match[3]), stoll(match[4]), stoll(match[5]));

	}

	//setup for parsing of my ticket
	std::getline(file, line);
	std::getline(file, line);
	MyTicket = parseTicket(line);
	std::getline(file, line);
	std::getline(file, line);

	
	long long error = 0;
	while (std::getline(file, line))
	{
		std::vector<long long> ticket = parseTicket(line);
		bool ticketGood = true;
		for(long long value : ticket)
		{
			//check for valid values
			auto validvalue = [&](auto& keyvalue) { return valid(keyvalue.first, value); };

			if (std::none_of(std::begin(rules), std::end(rules), validvalue))
			{
				error += value;
				ticketGood = false;
			}
		}
		if (ticketGood) 
			GoodTickets.push_back(move(ticket));
		
	}

	std::cout << "The error in tickets data are "<< error << std::endl;
}

long long departureTime() 
{
	std::unordered_map<std::string, unsigned long long> assignedrules;
	std::unordered_set<std::string> unassingedrules;
	std::vector<std::string> match;

	for (auto& keyvalue : rules)
	{
		unassingedrules.insert(keyvalue.first);
	}
	while (assignedrules.size() < rules.size())
	{
		for (unsigned long long col = 0u; col < MyTicket.size(); ++col)
		{
			match.clear();
			for (auto& rule : unassingedrules) 
			{
				auto validvalue = [&](auto& keyvalue) { return valid(rule, keyvalue[col]); };
				if (std::all_of(std::begin(GoodTickets), std::end(GoodTickets), validvalue))
					match.push_back(rule);
			}
			if (match.size() == 1u) 
			{
				unassingedrules.erase(match[0]);
				assignedrules[match[0]] = col;
			}
		}
	}

	long long counter = 1;
	for (auto& [key, value] : assignedrules)
	{
		if (key.find("departure") != std::string::npos) {
			counter *= MyTicket[value];
		}
	}

	return counter;
}



int main()
{
	GetInput("Day16Data.txt");

	std::cout << "departureTime tickets data are " << departureTime() << std::endl;
}
