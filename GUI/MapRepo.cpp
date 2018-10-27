#include "MapRepo.h"
#include "Repository.h"
#include <random>

int MapRepo::adauga(const Film& f)
{
	aruncaEroareCuProbabilitate();
	if (dictionar.size() == 0) dictionar.insert(std::make_pair(0, f));
	else
	{
		int indice = 0;
		int c = 0;
		int gasit = 0;
		for (const auto&el : dictionar)
		{
			if (indice != el.first && gasit == 0)
				c = indice, gasit = 1;
			indice++;
		}
		if (gasit == 1)
			dictionar.insert(std::make_pair(c, f));
		else dictionar.insert(std::make_pair(indice, f));
	}
	return 0;
}
int MapRepo::sterge(int id)
{
	aruncaEroareCuProbabilitate();
	const int poz = findId(id);
	dictionar.erase(poz);
	return 0;
}
int MapRepo::modifica(int id, const Film& film)
{
	aruncaEroareCuProbabilitate();
	const int poz = findId(id);
	dictionar[poz] = film;
	return 0;
}
Film MapRepo::existaTitlu(const string& titlu)
{
	aruncaEroareCuProbabilitate();
	Film f;
	int ok = 0;
	for (const auto&el : dictionar)
	{
		if (el.second.getTitlu() == titlu)
			f = el.second, ok = 1;
	}
	if (ok == 1) return f;
	throw RepositoryException("Nu s-a gasit un film cu acest titlu!\n");
}
int MapRepo::findId(const int& id)
{
	aruncaEroareCuProbabilitate();
	int poz = 0;
	for (const auto& el : dictionar)
	{
		if (el.first == id)
			return poz;
		poz++;
	}
	throw RepositoryException("Nu exista filmul!\n");
}
Film MapRepo::getFilmById(const int& id)
{
	aruncaEroareCuProbabilitate();
	for (const auto&el : dictionar)
	{
		if (el.first == id)
			return el.second;
	}
	throw RepositoryException("Nu exista id-ul\n");
}
void MapRepo::aruncaEroareCuProbabilitate()
{
	std::mt19937 mt{ std::random_device{}() }; //random number engine; random_device use PRNG as mt19937
	std::uniform_int_distribution<> dist(0, 100);
	int random = dist(mt);
	if (random < this->probabilitate * 100)
	{
		throw ProbilitateException("Prinsa de probabilitate");
	}
}
int MapRepo::getId(const Film& film)
{
	aruncaEroareCuProbabilitate();
	for (const auto& el : dictionar)
	{
		if (el.second.getTitlu() == film.getTitlu() &&
			el.second.getGen() == film.getGen() &&
			el.second.getAn() == film.getAn() &&
			el.second.getActor() == film.getActor())
			return el.first;
	}
	throw RepositoryException("Nu exista filmul!\n");
}

vector<std::pair<int, Film>> MapRepo::getAll() const noexcept
{
	vector <std::pair<int, Film>> rez;
	for (const auto& pair : dictionar)
	{
		rez.push_back(std::make_pair(pair.first, pair.second));
	}
	return rez;
}
ostream& operator<<(ostream& out, const ProbilitateException& ex)
{
	out << ex.msg;
	return out;
}
