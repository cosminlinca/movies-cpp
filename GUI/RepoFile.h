#pragma once
#include "Film.h"
#include "Repository.h"
class RepoFile : public Repository
{
private:
	std::string fileName;
	void loadFromFile();
	void writeToFile();
public:
	RepoFile(std::string fileName) : Repository(), fileName{ fileName }
	{
		loadFromFile();
	}
	int adauga(const Film& film) override
	{
		Repository::adauga(film);
		writeToFile();
		return 0;
	}
	int sterge(int id) override
	{
		Repository::sterge(id);
		writeToFile();
		return 0;
	}
	int modifica(int id, const Film& film) override
	{
		Repository::modifica(id, film);
		writeToFile();
		return 0;
	}

};
