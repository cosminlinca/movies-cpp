#include <fstream>
#include "RepoFile.h"
void RepoFile::loadFromFile()
{
	std::ifstream fin(fileName);
	while (!fin.eof()) //while file is not at the end
	{
		std::string titlu;
		std::string gen;
		int an;
		std::string actor;
		fin >> titlu;
		fin >> gen;
		fin >> an;
		fin >> actor;
		if (fin.eof()) break; //linie goala?!

		//c_str - This array includes the same sequence of characters that make up the value of 
		//        the string object plus an additional terminating null-character ('\0') at the end.

		Film film{ titlu.c_str(), gen.c_str(), an, actor.c_str() };
		RepoFile::adauga(film);
	}
	fin.close();
}
void RepoFile::writeToFile()
{
	std::ofstream fout(fileName);
	for (auto& f : getAll())
	{
		fout << f.second.getTitlu();
		fout << std::endl;
		fout << f.second.getGen();
		fout << std::endl;
		fout << f.second.getAn();
		fout << std::endl;
		fout << f.second.getActor();
		fout << std::endl;
	}
	fout.close();
}
