#pragma once
#include "Repository.h"
#include "AbstractRepo.h"
#include "MapRepo.h"
#include "Validator.h"
#include "InchirieriCos.h"
#include "Undo.h"
#include "Export.h"
#include "Observer.h"
#include <memory>

class Service
{
private:
	AbstractRepo & repo;
	Validator &val;

	InchiriereCos cos;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	std::vector<Observer*> curiosi;

	void notifyCuriosi()
	{
		for (auto c : curiosi)
		{
			c->update();
		}
	}
public:

	//Initializare service
	Service(AbstractRepo &repo, Validator &val) noexcept : repo{ repo }, val{ val } {}
	//Nu se poate copia un service
	Service(const Service& ot) = delete;

	/*
	Se adauga un film
	in: titlu - titlul unui film: string
	gen   - genul unui film: string
	an    - anul unui film: int
	actor - actorul unui film: string
	*/
	//void suntCurios(Observer* o);
	void notifica();
	void suntCurios(Observer* o);

	void adauga(const std::string&, const std::string&, const int&, const std::string&);

	//Se sterge un film cu un id specific
	//in: id-ul filmului
	void sterge(int);

	/*
	Se modifica un film specificat prin id
	in: id - id-ul filmului din lista
	titlu - noul titlu al filmului: string
	gen   - noul gen al filmului: string
	an    - noul an al filmului: int
	actor - noul actor al filmului: string
	*/
	void modifica(int, const std::string&, const std::string&, const int&, const std::string&);

	//Static member functions are not associated with any object
	//Static member functions cannot be virtual, const, or volatile.
	//Se compara doua filme dupa titlu
	static bool criteriuDupaTitlu(std::pair<int, Film>, std::pair<int, Film>);
	//Se compara doua filme dupa actor
	static bool criteriuDupaActor(std::pair<int, Film>, std::pair<int, Film>);

	//Se sorteaza lista dupa titlu
	vector <std::pair<int, Film>> sorteazaDupaTitlu() const;

	//Se sorteaza lista dupa actor
	vector <std::pair<int, Film >> sorteazaDupaActor() const;

	/*Functie generica de sortare
	in: referinta catre lista de sortat
	o functie de comparare: tip bool
	out: se returneaza lista sortata
	*/
	vector<std::pair<int, Film>> genericSort(vector<std::pair<int, Film>>, bool(*functieDeComparare)(std::pair<int, Film>, std::pair<int, Film>)) const;
	//Toata lista
	vector<std::pair<int, Film>> getAll() const noexcept
	{
		return repo.getAll();
	}

	/*
	Se filtreaza lista dupa un titlu specific
	in: titlu: string
	out: se returneaza o lista care contine toate obiectele cu stringul specific
	*/
	vector <std::pair<int, Film>> filtruDupaTitlu(std::string) const;

	vector <std::pair<int, Film>> filtruDupaAn(const int& an) const;

	//Se adauga in cos un film
	const vector<Film>& addToCos(const std::string& titlu);

	//Golirea completa a cosului
	const vector<Film>& golesteCos();

	//Se adauga in cos un numar fix de filme 
	const vector<Film>& addRandom();

	const vector<Film>& getCos()
	{
		return cos.lista();
	}

	void undo();

	void exportaCosCVS(std::string fileName);

	void exportaCosHTML(std::string fileName);
};