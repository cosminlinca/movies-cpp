/*
lambda captures
[a,&b] where a is captured by copy and b is captured by reference.
[this] captures the current object (*this) by reference
[&] captures all automatic variables used in the body of the lambda by reference and current object by reference if exists
[=] captures all automatic variables used in the body of the lambda by copy and current object by reference if exists
[] captures nothing
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Service.h"
#include "Film.h"
#include "Undo.h"
#include "Service.h"

using namespace std;

void Service::notifica()
{
	notifyCuriosi();
}

void Service::suntCurios(Observer * o)
{
	curiosi.push_back(o);
}

void Service::adauga(const std::string& titlu, const std::string& gen, const int& an, const std::string& actor)
{
	Film film = Film::Film(titlu, gen, an, actor);
	this->val.validate(film);
	this->repo.adauga(film);
	auto id = this->repo.getId(film);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, id));
	notifica();
}

void Service::sterge(int id)
{
	Film filmSters = this->repo.getFilmById(id);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, filmSters));
	this->repo.sterge(id);

}

void Service::modifica(int id, const std::string& titlu, const std::string& gen, const int& an, const std::string& actor)
{
	Film filmVechi = this->repo.getFilmById(id);
	Film film = Film::Film(titlu, gen, an, actor);
	this->val.validate(film);
	this->repo.modifica(id, film);
	undoActions.push_back(std::make_unique<UndoUpdate>(repo, id, filmVechi));
}

void Service::undo()
{
	if (undoActions.empty())
		throw exception{ "Nu mai exista operatii! \n" };

	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<std::pair<int, Film>> Service::genericSort(vector<std::pair<int, Film>> lista, bool(*functieDeComparare)(std::pair<int, Film> a, std::pair<int, Film>b)) const
{
	vector <std::pair<int, Film>> listaNoua;
	for (const auto&el : lista)
		listaNoua.push_back(el);

	sort(listaNoua.begin(), listaNoua.end(), functieDeComparare);
	return listaNoua;
}
bool Service::criteriuDupaTitlu(std::pair<int, Film> a, std::pair<int, Film> b)
{
	std::string titlu1 = a.second.getTitlu();
	std::string titlu2 = b.second.getTitlu();
	return titlu1 < titlu2;
}
bool Service::criteriuDupaActor(std::pair<int, Film> a, std::pair<int, Film> b)
{
	std::string actor1 = a.second.getActor();
	std::string actor2 = b.second.getActor();
	return actor1 < actor2;
}
vector<std::pair<int, Film>> Service::sorteazaDupaTitlu() const
{
	auto all = getAll();
	return genericSort(all, criteriuDupaTitlu);
}
vector<std::pair<int, Film>> Service::sorteazaDupaActor() const
{
	auto all = getAll();
	return genericSort(all, criteriuDupaActor);
}

vector<std::pair<int, Film>> Service::filtruDupaTitlu(std::string titlu) const
{
	vector <std::pair<int, Film>> rez;
	auto all = getAll();
	//copy_if
	copy_if(all.begin(), all.end(), std::back_inserter(rez), [titlu](std::pair<int, Film> el) {return el.second.getTitlu() == titlu; });
	/*
	int contor = 0;
	for (const auto&el: all)
	{
	if (el.second.getTitlu() == titlu)
	rez.push_back(std::make_pair(contor++,el.second));
	}
	*/
	return rez;

}
vector<std::pair<int, Film>> Service::filtruDupaAn(const int& an) const
{
	vector <std::pair<int, Film>> rez;
	auto all = getAll();
	int contor = 0;
	for (const auto&el : all)
	{
		if (el.second.getAn() == an)
			rez.push_back(std::make_pair(contor++, el.second));
	}
	return rez;

}

const vector<Film>& Service::addToCos(const std::string& titlu)
{
	Film f = repo.existaTitlu(titlu);
	cos.adauga(f);
	notifica();
	return cos.lista();
}
const vector<Film>& Service::golesteCos()
{
	cos.goleste();
	notifica();
	return cos.lista();
}
const vector<Film>&Service::addRandom()
{
	vector<Film> ListaFilme;
	for (const auto& el : repo.getAll())
		ListaFilme.push_back(el.second);
	ifstream fin("fisier.txt");
	cos.goleste();
	int numar;
	fin >> numar;
	cos.umpleAleator(numar, ListaFilme);
	notifica();
	fin.close();
	//cos.umpleAleator(cate, ListaFilme);
	return cos.lista();
}

void Service::exportaCosCVS(std::string fileName)
{
	exportToCVS(fileName, cos.lista());
}

void Service::exportaCosHTML(std::string fileName)
{
	exportToHTML(fileName, cos.lista());
}