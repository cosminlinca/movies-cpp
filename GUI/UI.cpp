#include <iostream>
#include "UI.h"
#include <string>
#include <stdio.h>
#include <stddef.h>
using namespace std;

void UI::meniu()
{
	std::cout << "Optiuni: " << std::endl;
	std::cout << "1  -  Adauga film." << std::endl;
	std::cout << "2  -  Afiseaza filme." << std::endl;
	std::cout << "3  -  Sterge film" << std::endl;
	std::cout << "4  -  Modifica film" << std::endl;
	std::cout << "5  -  Sorteaza dupa titlu" << std::endl;
	std::cout << "6  -  Sorteaza dupa actor" << std::endl;
	std::cout << "7  -  Filtru dupa titlu" << std::endl;
	std::cout << "8  -  Filtru dupa an" << std::endl;
	std::cout << "9. -  Adauga in cos" << std::endl;
	std::cout << "10 -  Goleste cos" << std::endl;
	std::cout << "11 -  Random in cos" << std::endl;
	std::cout << "12 -  Undo         " << std::endl;
	std::cout << "13 -  Exporta CVS" << std::endl;
	std::cout << "14 -  Exporta HTML" << std::endl;
	std::cout << "0 - EXIT " << std::endl;
}

void UI::printAll(vector<std::pair<int, Film>> all)
{
	if (all.size() == 0) cout << "Lista VIDA! " << endl;
	for (const auto& el : all)
	{
		int id = el.first;
		std::string titlu = el.second.getTitlu();
		std::string gen = el.second.getGen();
		int an = el.second.getAn();
		std::string actor = el.second.getActor();
		cout << id << " " << titlu << " " << gen << " " << an << " " << actor << endl;
	}
}
void UI::print()
{
	vector<std::pair<int, Film>> all = service.getAll();
	printAll(all);
}
void UI::add()
{
	cout << "Titlu: ";
	std::string titlu;
	getline(cin, titlu);
	cout << "Gen: ";
	std::string gen;
	getline(cin, gen);
	cout << "An: ";
	std::string an;
	getline(cin, an);
	const int anInt = stoi(an);
	cout << "Actor: ";
	std::string actor;
	getline(cin, actor);
	this->service.adauga(titlu, gen, anInt, actor);
}

void UI::remove()
{
	int id;
	cout << "ID = ";
	cin >> id;
	this->service.sterge(id);
}

void UI::update()
{
	int id;
	cout << "ID = ";
	cin >> id;
	cin.ignore();
	cout << "Titlu nou: ";
	std::string titlu;
	getline(cin, titlu);
	cout << "Gen nou: ";
	std::string gen;
	getline(cin, gen);
	cout << "An nou: ";
	std::string an;
	getline(cin, an);
	const int anInt = stoi(an);
	cout << "Actor nou: ";
	std::string actor;
	getline(cin, actor);
	this->service.modifica(id, titlu, gen, anInt, actor);
}

void UI::sorteazaDupaTitlu()
{
	vector<std::pair<int, Film>> rez;
	rez = service.sorteazaDupaTitlu();
	printAll(rez);
}
void UI::sorteazaDupaActor()
{
	vector<std::pair<int, Film>> rez;
	rez = service.sorteazaDupaActor();
	printAll(rez);
}
void UI::filtreazaDupaTitlu()
{
	std::string s;
	cout << "Dati titlul: ";
	cin >> s;
	vector<std::pair<int, Film>> filtrata = service.filtruDupaTitlu(s);
	printAll(filtrata);
}
void UI::filtreazaDupaAn()
{
	std::string an;
	cout << "Dati an: ";
	getline(cin, an);
	const int anInt = stoi(an);
	vector<std::pair<int, Film>> filtrata = service.filtruDupaAn(anInt);
	printAll(filtrata);
}
void UI::adaugaInCos()
{
	cout << "Titlu: ";
	std::string titlu;
	getline(cin, titlu);
	auto cos = service.addToCos(titlu);
	cout << "Cosul contine:\n";
	for (const auto& el : cos)
		cout << el.getTitlu() << " " << el.getGen() << endl;
}
void UI::golesteCos()
{
	auto cos = service.golesteCos();
	if (cos.size() == 0) cout << "Cos gol!\n";
}
void UI::adaugaRandom()
{
	std::string cate;
	//cout << "Cate sa se generere? :  ";
	//getline(cin, cate);
	//const int cateI = stoi(cate);
	//auto cos = service.addRandom(cateI);
	auto cos = service.addRandom();

	cout << "Cosul contine:\n";
	for (const auto& el : cos)
		cout << el.getTitlu() << " " << el.getGen() << endl;
}
void UI::cvsExport()
{
	cout << "CVS file: ";
	std::string file;
	getline(cin, file);
	service.exportaCosCVS(file);
}
void UI::htmlExport()
{
	cout << "HTML file: ";
	std::string file;
	getline(cin, file);
	service.exportaCosHTML(file);
}
void UI::startUI()
{
	while (true)
	{
		UI::meniu();
		int cmd{ 0 };
		cout << "Introduceti comanda: ";
		cin >> cmd;
		cin.ignore();
		if (cmd == 0) break;
		try
		{
			switch (cmd)
			{
			case 1:
				this->add();
				break;
			case 2:
				this->print();
				break;
			case 3:
				this->remove();
				break;
			case 4:
				this->update();
				break;
			case 5:
				this->sorteazaDupaTitlu();
				break;
			case 6:
				this->sorteazaDupaActor();
				break;
			case 7:
				this->filtreazaDupaTitlu();
				break;
			case 8:
				this->filtreazaDupaAn();
				break;
			case 9:
				this->adaugaInCos();
				break;
			case 10:
				this->golesteCos();
				break;
			case 11:
				this->adaugaRandom();
				break;
			case 12:
				service.undo();
				this->print();
				break;
			case 13:
				this->cvsExport();
				break;
			case 14:
				this->htmlExport();
				break;
			default:
				cout << "Comanda invalida!" << endl;
				break;
			}
		}
		catch (ValidateException& ex)
		{
			cout << ex << endl;
		}
		catch (RepositoryException& ex)
		{
			cout << ex << endl;
		}
		catch (exception &ex)
		{
			std::cerr << ex.what();
		}
		catch (ProbilitateException &ex)
		{
			cout << ex << endl;
		}
	}
}

