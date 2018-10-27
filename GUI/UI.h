#pragma once
#include "Service.h"
class UI
{
private:
	Service & service;
	void meniu();
	void add();

	void remove();
	void update();
	void sorteazaDupaTitlu();
	void sorteazaDupaActor();
	void filtreazaDupaTitlu();
	void filtreazaDupaAn();
	void print();
	void printAll(vector<std::pair<int, Film>> all);

	void adaugaInCos();
	void golesteCos();
	void adaugaRandom();

	void cvsExport();

	void htmlExport();

public:
	UI(Service &service) noexcept : service{ service } {}
	UI(const UI& ot) = delete;

	void startUI();
};