#include "GUI.h"
#include "COSGUI.h"
#include "COSReadOnlyGUI.h"
#include <QtWidgets/QApplication>
#include "Validator.h"
#include "Repository.h"
#include "RepoFile.h"
#include "MapRepo.h"
#include "Service.h"
#include "AbstractRepo.h"
#include "UI.h"
#include "Lista.h"
#include "Teste.h"

void teste()
{
	testAdaugaRepo();
	testStergeRepo();
	testModificaRepo();
	testAdaugaService();
	testStergeService();
	testUpdateService();
	testSortFiltru();
	testDomain();
	testeCos();
	testeUndo();
	testeExport();
	testeMap();
	testeRepoFile();
}

int main(int argc, char *argv[])
{
	teste();
	system("clear");
	Repository repo;
	RepoFile repoFile{ "filme.txt" };
	Repository ARepo;
	MapRepo map{ 1.0 };
	Validator val;
	Service service{ repo, val };
	//UI ui{ service };
	service.adauga("TheHobbit", "adventure", 2000, "Dan");
	service.adauga("Inferno", "action", 2006, "Marius");
	service.adauga("Centrale", "drama", 2002, "Andrei");
	service.adauga("Musica", "drama", 2000, "Adriana");
	service.adauga("PiratiiDinCaraibe", "action", 2007, "Michael");
	service.adauga("Insidious", "horror", 2008, "Anna");

	//ui.startUI();


	QApplication a(argc, argv);
	GUI gui{ service };
	gui.show();

	COSGUI cosgui{ service };
	cosgui.show();

	COSReadOnlyGUI draw{ service };
	draw.show();
	/*
	GUI gui3{ service };
	gui3.show();
	*/

	return a.exec();
}