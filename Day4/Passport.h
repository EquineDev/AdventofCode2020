#pragma once
#ifndef PASSPORT_H 
#define PASSPORT_H

#endif
#include <string>
class Passport
{
	
	
public:

	void ClearFields();
	void SetField(std::string key, std::string val);
	bool isValid();
	bool isValidStrict();
};

