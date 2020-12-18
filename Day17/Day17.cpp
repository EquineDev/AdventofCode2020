// Day17.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>

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

long long Count3DNeighbors(long long x, long long cx, long long y, long long cy, long long z, long long cz, const vector<vector<vector<bool>>>& Matrix)
{
	long long count = 0;
	for (long long iz = std::max(0ll, z - 1); iz < std::min(z + 2, cz); ++iz)
	{
		for (long long iy = std::max(0ll, y - 1); iy < std::min(y + 2, cy); ++iy)
		{
			for (long long ix = std::max(0ll, x - 1); ix < std::min(x + 2, cx); ++ix)
			{
				if (Matrix[iz][iy][ix])
					++count;

			}
		}
	}
	if (Matrix[z][y][x])
		--count;
	return count;
}

long long Count4DNeighbors(long long x, long long cx, long long y, long long cy, long long z, long long cz, long long w, long long cw, const vector<vector<vector<vector<bool>>>>& Matrix)
{

	long long count = 0;
	for (long long iw = max(0ll, w - 1); iw < min(w + 2, cw); ++iw) 
	{
		for (long long iz = max(0ll, z - 1); iz < min(z + 2, cz); ++iz) 
		{
			for (long long iy = max(0ll, y - 1); iy < min(y + 2, cy); ++iy) 
			{
				for (long long ix = max(0ll, x - 1); ix < min(x + 2, cx); ++ix) 
				{

					if (Matrix[iw][iz][iy][ix]) 
						++count;
					
				}
			}
		}
	}

	if (Matrix[w][z][y][x])  
		--count; 

	return count;

}

long long Matrix3D(long long cylceCount)
{

	long long cx = (2 * cylceCount) + Data[0].size();
	long long cy = (2 * cylceCount) + Data.size();
	long long cz = (2 * cylceCount) + 1;

	vector<vector<vector<bool>>> Matrix(cz, vector<vector<bool>>(cy, vector<bool>(cx, false)));

	for (auto y = 0u; y < Data.size(); ++y)
	{
		for (auto x = 0u; x < Data[y].size(); ++x)
		{
			Matrix[cylceCount][cylceCount + y][cylceCount + x] = Data[y][x] == '#';
		}
	}



	long long  lastcount = 0;
	for (long long cycle = 0; cycle < cylceCount; ++cycle)
	{
		lastcount = 0;
		auto newMatrix = Matrix;
		for (long long z = 0; z < cz; ++z)
		{
			for (long long y = 0; y < cy; ++y)
			{
				for (long long x = 0; x < cx; ++x)
				{
					long long neighbors = Count3DNeighbors(x, cx, y, cy, z, cz, Matrix);

					if (Matrix[z][y][x])
						newMatrix[z][y][x] = (neighbors == 2) || (neighbors == 3);

					else
						newMatrix[z][y][x] = (neighbors == 3);

					if (newMatrix[z][y][x])
						++lastcount;
				}
			}
		}
		Matrix = move(newMatrix);
	}
	return lastcount;


}

long long Matrix4D(long long cylceCount)
{

	long long cx = (2 * cylceCount) + Data[0].size();
	long long cy = (2 * cylceCount) + Data.size();
	long long cz = (2 * cylceCount) + 1;
	long long cw = (2 * cylceCount) + 1;

	vector<vector<vector<vector<bool>>>> Matrix(cw, vector<vector<vector<bool>>>(cz, vector<vector<bool>>(cy, vector<bool>(cx, false))));

	for (auto y = 0u; y < Data.size(); ++y)
	{
		for (auto x = 0u; x < Data[y].size(); ++x) 
		{
			Matrix[cylceCount][cylceCount][cylceCount + y][cylceCount + x] = Data[y][x] == '#';
		}
	}



	long long  Lastcount = 0;

	for (long long cycle = 0; cycle < cylceCount; ++cycle) {
		Lastcount = 0;
		auto newMatrix = Matrix;
		for (long long w = 0; w < cw; ++w) 
		{
			for (long long z = 0; z < cz; ++z) 
			{
				for (long long y = 0; y < cy; ++y) 
				{
					for (long long x = 0; x < cx; ++x) 
					{
						long long  neighbors = Count4DNeighbors(x,cx, y,cy, z,cz, w,cw, Matrix);

						if (Matrix[w][z][y][x])
							newMatrix[w][z][y][x] = (neighbors == 2) || (neighbors == 3);
						else 
							newMatrix[w][z][y][x] = (neighbors == 3);
						
						if (newMatrix[w][z][y][x])
							++Lastcount;
					}
				}
			}
		}
		Matrix = move(newMatrix);
	}

	return Lastcount;


}

int main()
{
	GetInput("Day17Data.txt");
	std::cout << Matrix3D(6) << ":PART1\n";
	std::cout << Matrix4D(6) << ":PART2\n";
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
