// Day14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <bitset>
#include <numeric>

std::regex mask_pattern{ R"(mask = (\w+))" };
std::regex mem_pattern{ R"(mem\[(\d+)\] = (\d+))" };
std::vector<std::string> Data;

using namespace std;
void GetInput(std::string  filename)
{
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		Data.push_back(line);
	}
	file.close();
}

void MemoryProblem() 
{
	unsigned long long mask0 = 0u, mask1 = 0u;
	std::unordered_map<unsigned long long, unsigned long long> memMap1, memMap2;
	std::vector<int> fbits;
	for (auto line : Data) 
	{
			smatch match;
			if (regex_match(line, match, mask_pattern)) {
				bitset<36> tmp0, tmp1;
				string mask = match[1];

				fbits.clear();
				for (auto i = 0; i < 36; ++i) 
				{
					tmp0[i] = mask[35 - i] != '0';
					tmp1[i] = mask[35 - i] == '1';

					if (mask[35 - i] == 'X') 
						fbits.push_back(i);
					
				}
				mask0 = tmp0.to_ullong();
				mask1 = tmp1.to_ullong();
			}
			else if (regex_match(line, match, mem_pattern)) 
			{
				unsigned long long addr = stoull(match[1]);
				unsigned long long value1 = stoull(match[2]), value2 = value1;
				
				value1 &= mask0;
				value1 |= mask1;
				memMap1[addr] = value1;
				
				addr |= mask1;
				for (unsigned long long bits = 0u; bits < (1u << fbits.size()); ++bits)
				{
					bitset<36> addr_bits{ addr };

					for (auto i = 0u; i < fbits.size(); ++i)
					{
						addr_bits[fbits[i]] = (bits & (1u << i)) != 0;
					}
					memMap2[addr_bits.to_ullong()] = value2;
				}
			}

		}

		auto add_vals = [](unsigned long long p, auto& kv) { return p + kv.second; };
		std::cout << "Memory Adresss:" <<accumulate(begin(memMap1), end(memMap1), 0ull, add_vals) << endl;
		std::cout << " Part 2Memory Adresss:" << accumulate(begin(memMap2), end(memMap2), 0ull, add_vals) << endl;
	
}
int main()
{
	GetInput("Day14Data.txt");
	MemoryProblem();
	
	std::string line;
	
	return 0;
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
