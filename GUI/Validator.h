#pragma once
#include <string>
#include "Film.h"
#include <vector>
using namespace std;

class ValidateException
{
public:
	vector<string> msgs;
	ValidateException(const vector<string>& errors) :msgs{ errors } {}

	//friend function
	friend ostream& operator<<(ostream& out, const ValidateException& ex);

	std::string getMessage()
	{
		string s = "";
		for (const auto&msg : msgs)
		{
			s = s + msg + "\n";
		}
		return s;
	}
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator
{
public:
	void validate(const Film& l);
};
#pragma once
