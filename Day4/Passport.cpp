#include "Passport.h"

class Passport {
public:

	std::string byr;
	std::string iyr;
	std::string eyr;
	std::string hgt;
	std::string hcl;
	std::string ecl;
	std::string pid;
	std::string cid;


	void ClearFields()
	{

		byr.clear();
		iyr.clear();
		eyr.clear();
		hgt.clear();
		hcl.clear();
		ecl.clear();
		pid.clear();
		cid.clear();

	}

	void SetField(std::string key, std::string value)
	{

		
		if (key == "byr")
			byr = value;
		if (key == "iyr")
			iyr = value;
		if (key == "eyr")
			eyr = value;
		if (key == "hgt")
			hgt = value;
		if (key == "hcl")
			hcl = value;
		if (key == "ecl")
			ecl = value;
		if (key == "pid")
			pid = value;
		if (key == "cid")
			cid = value;


	}
	bool isValid()
	{
		return !(byr.empty() || iyr.empty() || eyr.empty() || hgt.empty() || hcl.empty() || ecl.empty() || pid.empty());
	}
	bool isValidStrict()
	{

		if (!isValid())
			return false;

		//check to see years are valid
		if (byr.empty() || stoi(byr) < 1920 || stoi(byr) > 2002)
			return false;

		if (iyr.empty() || stoi(iyr) < 2010 || stoi(iyr) > 2020)
			return false;

		if (eyr.empty() || stoi(eyr) < 2020 || stoi(eyr) > 2030)
			return false;


		//check heght in inch or cm
		std::string measurment = hgt.substr(hgt.size() - 2);
		// get hight number 
		int number = stoi(hgt);
		

		//check that all heigh data is valid
		if (measurment == "cm" && (number < 150 || number > 193))
			return false;
		if (measurment == "in" && (number < 59 || number > 76))
			return false;
		if (measurment != "cm" && measurment != "in")
			return false;

		//check to see if have # and 6 digits
		if (hcl[0] != '#' || hcl.size() != 7)
			return false;
		
		//check to see hex values are vaild
		for (int i = 1; i < hcl.size(); i++) {
			
			if (!((hcl[i] >= 48 && hcl[i] <= 57) || (hcl[i] >= 97 && hcl[i] <= 102)))
				return false;
		}

		//check eye color rule

		if (ecl != "amb" && ecl != "blu" && ecl != "brn" && ecl != "gry" && ecl != "grn" && ecl != "hzl" && ecl != "oth")
			return false;

		//reset out counter
		number = 0;

		//check password id
		for (int i = 0; i < pid.size(); i++) {

			if (pid[i] < 48 ^ pid[i] > 57)
				return false;

			number ++;
		}
		if (number != 9)
			return false;

		

		return true;
	}

};
