#include "Repository.h"
#include <assert.h>
#include <algorithm>

int Repository::adauga(const Film& film)
{
	if (exista(film))
	{
		throw RepositoryException("Film existent!\n ");
	}
	if (all.size() == 0) all.push_back(std::make_pair(0, film));
	else
	{
		int indice = 0;
		int c = 0;
		int gasit = 0;
		for (const auto&el : all)
		{
			if (indice != el.first && gasit == 0)
				c = indice, gasit = 1;
			indice++;
		}
		if (gasit == 1)
			all.push_back(std::make_pair(c, film));
		else all.push_back(std::make_pair(indice, film));
	}

	return 0;
}

int Repository::sterge(int id)
{
	if (!existaId(id))
	{
		throw RepositoryException("Film inexistent!\n ");
	}

	const int poz = findId(id);
	all.erase(all.begin() + poz);
	return 0;
}

int Repository::modifica(int id, const Film& film)
{
	if (!existaId(id))
	{
		throw RepositoryException("Film inexistent!\n ");
	}

	const int poz = findId(id);
	all[poz] = std::make_pair(id, film);
	return 0;

}
bool Repository::existaId(const int& id)
{
	try
	{
		findId(id);
		return true;
	}
	catch (RepositoryException&)
	{
		return false;
	}

}
int Repository::findId(const int& id)
{
	/*
	std::vector<pair<int,Film>>::const_iterator it;
	it = std::find_if(all.begin(), all.end(), [&](pair<int, Film>el) {el.first == id; });
	if(it == all.end())
		throw RepositoryException("Nu exista filmul!");
	else return false;
	*/
	int poz = 0;
	for (const auto&el : all)
	{
		if (el.first == id)
			return poz;
		poz++;
	}
	throw RepositoryException("Nu exista filmul!\n");

}
bool Repository::exista(const Film& film)
{
	try
	{
		find(film);
		return true;
	}
	catch (RepositoryException&)
	{
		return false;
	}

}
Film Repository::existaTitlu(const string& titlu)
{
	Film f;
	int ok = 0;
	for (const auto&el : all)
	{
		if (el.second.getTitlu() == titlu)
			f = el.second, ok = 1;

	}
	if (ok == 1) return f;
	throw RepositoryException("Nu s-a gasit un film cu acest titlu!\n");
}
int Repository::find(const Film& film)
{
	int poz = 0;
	for (const auto& el : all)
	{
		if (el.second.getTitlu() == film.getTitlu() &&
			el.second.getGen() == film.getGen() &&
			el.second.getAn() == film.getAn() &&
			el.second.getActor() == film.getActor())
			return poz;
		poz++;
	}
	throw RepositoryException("Nu exista filmul!\n");
}
int Repository::getId(const Film&film)
{
	for (const auto& el : all)
	{
		if (el.second.getTitlu() == film.getTitlu() &&
			el.second.getGen() == film.getGen() &&
			el.second.getAn() == film.getAn() &&
			el.second.getActor() == film.getActor())
			return el.first;
	}
	throw RepositoryException("Nu exista filmul!\n");
}
Film Repository::getFilmById(const int& id)
{
	for (const auto&el : all)
	{
		if (el.first == id)
			return el.second;
	}
	throw RepositoryException("Nu exista id-ul\n");
}
vector<std::pair<int, Film>> Repository::getAll() const noexcept
{
	return all;
}

ostream& operator<<(ostream& out, const RepositoryException& ex)
{
	out << ex.msg;
	return out;
}

