#include <string>

#pragma once


class Passport
{
	
	
public:
	Passport();
	void ClearFields();
	void SetField(std::string key, std::string val);
	bool isValid();
	bool isValidStrict();
	
protected:
	std::string byr;
	std::string iyr;
	std::string eyr;
	std::string hgt;
	std::string hcl;
	std::string ecl;
	std::string pid;
	std::string cid;
private:

};

