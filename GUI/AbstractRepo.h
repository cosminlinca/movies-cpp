#pragma once
#include "Film.h"
#include <string>
#include <vector>
using namespace std;
class AbstractRepo
{
public:
	AbstractRepo() {};
	virtual int adauga(const Film& film) = 0;
	virtual int sterge(int id) = 0;
	virtual int modifica(int id, const Film& film) = 0;
	virtual int findId(const int&id) = 0;
	virtual int getId(const Film& film) = 0;
	virtual Film getFilmById(const int& id) = 0;
	virtual Film existaTitlu(const string& titlu) = 0;
	virtual vector<std::pair<int, Film>> getAll() const noexcept = 0;
};