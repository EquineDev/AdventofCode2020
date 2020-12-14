#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


std::vector<int> busses;
std::vector<long long> BIGbusses;
std::vector<long long> BIGbussesOffSet;

int GetInputTimeAndBusses(std::string  filename)
{
	std::ifstream file(filename);
	std::string line;
	int time;
	bool HasGotTime = false;

	while (getline(file, line))
	{
		if (!HasGotTime)
		{
			time = std::stoi(line);
			HasGotTime = true;
			continue;
		}

		std::stringstream ss(line);
		for (int i; ss >> i;)
		{
			busses.push_back(i);
			while (ss.peek() == ',' || ss.peek() == 'x') 
			{
				ss.ignore(); 
			}
		}
	}
	file.close();
	return time;
}

 void BussesSetupForBIGDATA(std::string  filename) 
{
	 std::ifstream file(filename);
	 std::string line;
	 long long offset;
	 bool HasGotTime = false;

	 while (getline(file, line))
	 {
		 if (!HasGotTime)
		 {
			 long long time = std::stoll(line);
			 HasGotTime = true;
			 continue;
		 }

		 std::stringstream ss(line);
		 for (long long i; ss >> i;)
		 {

			 BIGbusses.push_back(i);
			 //setup our busses offset
			 if (BIGbusses.size() == 1)
				 BIGbussesOffSet.push_back(offset);
			 else
				 BIGbussesOffSet.push_back(i - offset);
			 while (ss.peek() == ',' || ss.peek() == 'x')
			 {
				 if (ss.peek() == 'x')
				 {
					 ss.ignore();
					 continue;
				 }
				 ss.ignore();
				 offset++;
			 }
		 }
	 }
	 file.close();
	 
}

 long long Inverse(long long num1, long long num2) 
 {
	 long long b0 = num2,  x0 = 0, x1 = 1;

	 if (num2 == 1) {
		 return 1;
	 }

	 while (num1 > 1) {
		 long long q = num1 / num2;
		 long long amb = num1 % num2;
		 num1 = num2;
		 num2 = amb;

		 long long xqx = x1 - q * x0;
		 x1 = x0;
		 x0 = xqx;
	 }

	 if (x1 < 0) {
		 x1 += b0;
	 }

	 return x1;
 }


void  RemainderTheoremChinese()
 {
	 long long M = 1;
	 for (auto val : BIGbusses)
	 {
		 M *= val; 
	 };

	 long long sum = 0;
	 for (int i  = 0; i < BIGbusses.size(); ++i)
	 {
		 long long Mi = M / BIGbusses[i];
		 sum += BIGbussesOffSet[i] * Mi * Inverse(Mi % BIGbusses[i], BIGbusses[i]);
	 }


	 std::cout << " The bus departs at :" << sum % M << std::endl;
	
 }

void BusDepartTimes(int time) 
{
	int bestBus = 0, waitTime = 9999;
	std::vector<int> departureTimes;
	for (auto bus : busses)
	{
		departureTimes.push_back(bus - (time % bus));
		if (bus - (time % bus) < waitTime) 
		{ 
			bestBus = bus;
			waitTime = (bus - (time % bus)); 
		}
	}
	std::cout <<  bestBus << " is the closest departing bus in " << waitTime << " minutes. Anwser Part1: " << bestBus * waitTime << std::endl;
}

void BusDepartTimesOffset() 
{

}

int main() 
{
	int time = GetInputTimeAndBusses("Day13Data.txt");
	BusDepartTimes(time);
	BussesSetupForBIGDATA("Day13Data.txt");
	RemainderTheoremChinese();
	system("Pause");
	


}