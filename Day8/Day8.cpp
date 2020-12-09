
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_set>
#include <unordered_map>

enum token
{
	nop,
	jmp,
	acc
};

struct instruction
{
	token token;
	int value;
};
struct result
{
	bool term;
	int acc;
};
std::vector<instruction> GameData;
std::unordered_map<std::string, token>  TokenTable = { {"acc",token::acc}, {"jmp",token::jmp}, {"nop",token::nop} };

void GetInput(std::string FileData)
{
	std::ifstream file(FileData);

	std::regex regexInsturction("(acc|jmp|nop) ([+-]\\d+)");
	std::string line;
	while (std::getline(file, line))
	{
		std::smatch match;
		std::regex_match(line, match, regexInsturction);
		GameData.push_back({ TokenTable[match[1]] , std::stoi(match[2]) });
	}

	file.close();
}

result Run() 
{
	int Countacc = 0, Countip = 0;
	std::unordered_set<int> seen;
	while (seen.find(Countip) == seen.end())
	{
		
		if (Countip == GameData.size())
			return { true, acc };

		seen.insert(Countip);
		switch (GameData[Countip].token)
		{
		case nop:
			Countip++;
			break;
		case jmp:
			Countip += GameData[Countip].value;
			break;
		case acc:
			Countacc += GameData[Countip].value;
			Countip++;
			break;
		default:
			break;
		}
	}
	return { false, Countacc };
}

int BeforeLoopingACC() 
{
	return Run().acc;
}


int AfterHotFixACC() 
{
	result result;
	for (int i = 0; i < GameData.size(); i++)
	{
		switch (GameData[i].token)
		{
		case nop:
			GameData[i].token = jmp;
			break;
		case jmp:

			GameData[i].token = nop;
			break;
		default:
			continue;
			break;
		}

		result = Run();
		if (result.term)
			return result.acc;
	
		switch (GameData[i].token)
		{
		case nop:
			GameData[i].token = jmp;
			break;
		case jmp:
			GameData[i].token = nop;
			break;
		default:
			break;
		}

	}

	return -1;


}
int main()
{
	GetInput("Test.txt");
	std::cout << "Test Data" << std::endl;
	std::cout << "ACC before LOOP: " << BeforeLoopingACC() << std::endl;
	std::cout << "ACC After HotFix: " << AfterHotFixACC() << std::endl;
	GameData.clear();
	GetInput("Day8Data.txt");
	std::cout << "Real Data" << std::endl;
	std::cout << "ACC before LOOP: " << BeforeLoopingACC() << std::endl;
	std::cout << "ACC After HotFix: " << AfterHotFixACC() << std::endl;
	system("Pause");
}
