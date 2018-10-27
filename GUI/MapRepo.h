#pragma once
#include "AbstractRepo.h"
#include <map>
#include <vector>
class ProbilitateException
{
	string msg;
public:
	ProbilitateException(string m) : msg{ m } {}
	friend ostream& operator<<(ostream& out, const ProbilitateException& ex);
};

class MapRepo : public AbstractRepo
{
private:
	std::map<int, Film> dictionar;
	double probabilitate;
public:
	MapRepo() {};
	MapRepo(double prob) : probabilitate{ prob } {}

	int adauga(const Film& f) override;
	int sterge(int id) override;
	int getId(const Film& f) override;
	int findId(const int& id) override;
	Film getFilmById(const int& id) override;
	int modifica(int id, const Film& film) override;
	Film existaTitlu(const string& titlu) override;
	void aruncaEroareCuProbabilitate();
	vector<std::pair<int, Film>> getAll() const noexcept override;

};