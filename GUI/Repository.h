#pragma once
#include "AbstractRepo.h"
//#include "DynamicVector.h"
#include "Lista.h"
#include "Film.h"
#include <string>
#include <vector>
using namespace std;

class Repository :public AbstractRepo
{
	//private:
	//Lista<std::pair<int, Film>> *all;
	std::vector <std::pair<int, Film>> all;
	int contor = 0;
public:
	//Initializare repository
	/*
	Repository() noexcept
	{
	auto l = new Lista<std::pair<int, Film>>();
	this->all = l;
	}
	//Pentru a nu se putea copia un repository
	Repository(const Repository& ot) = delete;
	//destructor repo
	~Repository()
	{
	delete all;
	}

	*/
	/*
	Se adauga un film in lista de filme
	in: un obiect de tip film
	*/
	int adauga(const Film& film) override;

	/*
	Se sterge un film cu un id unic din lista de filme
	in: id-ul unui film
	*/
	int sterge(int id) override;

	/*
	Inlocuieste un obiect de la un id specific, cu un alt id
	in: id - id-ul unui film din lista
	film - noul film
	*/
	int modifica(int id, const Film& film) override;

	//Se verifica existenta unui film 
	bool exista(const Film& film);
	//Se verifica existenta unui id unic
	bool existaId(const int&id);

	/*
	Se cauta un film in lista de filme
	in: film - un film
	out: pozitia la care se gaseste filmul, sau RepositoryException daca nu se gaseste
	*/
	int find(const Film& film);
	/*
	Se cauta un film cu un id specific in lista de filme
	in: id - id-ul unui film
	out: pozitia la care se gaseste filmul, sau RepositoryException daca nu se gaseste
	*/
	int findId(const int&id) override;

	int getId(const Film& film) override;
	Film getFilmById(const int& id) override;

	Film existaTitlu(const string& titlu) override;

	//Toata lista
	vector<std::pair<int, Film>> getAll() const noexcept override;
};

//clasa pentru exceptiile aruncate din Repository(ex: duplicate item);
class RepositoryException
{
public:
	string msg;

	RepositoryException(string m) : msg{ m } {}

	//functie friend 
	friend ostream& operator<<(ostream& out, const RepositoryException& ex);
};
