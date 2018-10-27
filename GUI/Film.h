#pragma once
#include <iostream>
class Film
{
private:
	std::string titlu;
	std::string gen;
	int an;
	std::string actor;
public:

	//Default constructor
	Film() noexcept;
	//Constructor de initializare
	Film(const std::string& titlu, const std::string& gen, const int& an, const std::string& actor);

	//Returneaza titlul
	std::string getTitlu() const { return titlu; }

	//Returneaza genul
	std::string getGen() const { return gen; }

	//Returneaza anul 
	int getAn() const noexcept { return an; }

	//Returneaza actorul
	std::string getActor() const { return actor; }

	//Seteaza titlul
	int setTitlu(std::string);

	//Seteaza genul
	int setGen(std::string);

	//Seteaza anul
	int setAn(int) noexcept;

	//Seteaza actorul
	int setActor(std::string);
	~Film();
};