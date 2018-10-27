#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include "RepoFile.h"
#include <assert.h>
#include <fstream>
#include <string>

//REPOSITORY test
void testAdaugaRepo()
{
	Repository repo;
	repo.adauga(Film{ "aaa","bbb",10,"ccc" });
	assert(repo.getAll().size() == 1);
	try
	{
		repo.adauga(Film{ "aaa","bbb",10,"ccc" });
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}
void testStergeRepo()
{
	Repository repo;
	repo.adauga(Film{ "aaa","bbb",10,"ccc" });
	repo.adauga(Film{ "aaa2","bbb2",11,"ccc2" });
	repo.adauga(Film{ "aaa3","bbb3",12,"ccc3" });
	repo.sterge(2);
	assert(repo.getAll().size() == 2);
	try
	{
		repo.sterge(7);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
	repo.sterge(0);
	assert(repo.getAll().size() == 1);
}
void testModificaRepo()
{
	Repository repo;
	repo.adauga(Film{ "aaa","bbb",10,"ccc" });
	repo.adauga(Film{ "aaa2","bbb2",11,"ccc2" });
	repo.modifica(0, Film{ "rrr","ttt",20,"ooo" });
	repo.modifica(1, Film{ "rrr","ppp",29,"oll" });
	try
	{
		repo.modifica(7, Film{ "gg","tt",29,"oo" });
	}
	catch (RepositoryException& ex)
	{
		cout << ex << endl; //<< operator
		assert(true);
	}
}

//SERVICE test
void testAdaugaService()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("movie", "actiune", 10, "dan");
	assert(srv.getAll().size() == 1);
	try
	{
		srv.adauga("", "actiune", 20, "dan");
	}
	catch (ValidateException& ex)
	{
		cout << ex << endl;
		assert(true);
	}
}
void testStergeService()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("movie", "actiune", 10, "dan");
	srv.sterge(0);
	assert(srv.getAll().size() == 0);
}
void testUpdateService()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("movie", "actiune", 10, "dan");
	srv.adauga("movie2", "drama", 20, "daniel");
	srv.modifica(1, "movie3", "thriller", 20, "man");
	Film f = srv.getAll()[1].second;
	assert(f.getGen() == "thriller");
}
void testSortFiltru()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("movie", "actiune", 10, "dan");
	srv.adauga("movie2", "drama", 14, "daniel");
	srv.adauga("movie3", "actiune", 12, "mihai");
	srv.adauga("movie4", "thriller", 20, "anca");

	auto rez = srv.sorteazaDupaActor();
	assert(rez.size() == 4);

	rez = srv.sorteazaDupaTitlu();
	assert(rez.size() == 4);

	vector<std::pair<int, Film>> rezF = srv.filtruDupaTitlu("movie");
	assert(rezF.size() == 1);

	rezF = srv.filtruDupaAn(12);
	assert(rezF.size() == 1);
}

//DOMAIN
void testDomain()
{
	Film f1{};
	Film f{ "movie", "actiune", 10, "dan" };
	f.setActor("mihai");
	assert(f.getActor() == "mihai");

	f.setAn(20);
	assert(f.getAn() == 20);

	f.setGen("drama");
	assert(f.getGen() == "drama");

	f.setTitlu("mv1");
	assert(f.getTitlu() == "mv1");
}
void testeCos()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("TheHobbit", "adventure", 2000, "Dan");
	srv.adauga("Inferno", "action", 2006, "Marius");
	srv.adauga("Centrale", "drama", 2002, "Andrei");
	srv.adauga("Musica", "drama", 2000, "Adriana");
	auto cos = srv.addToCos("Musica");
	assert(cos.size() == 1);

	cos = srv.golesteCos();
	assert(cos.size() == 0);
	cos = srv.addRandom();
	//assert(cos.size() == 3);
	cos = srv.golesteCos();
	assert(cos.size() == 0);

	try
	{
		cos = srv.addToCos("aaaaa");
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}
void testeUndo()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("TheHobbit", "adventure", 2000, "Dan");
	srv.adauga("Inferno", "action", 2006, "Marius");
	srv.adauga("Centrale", "drama", 2002, "Andrei");
	srv.adauga("Musica", "drama", 2000, "Adriana");

	srv.undo();
	assert(srv.getAll().size() == 3);
	srv.sterge(0);
	srv.undo();
	assert(srv.getAll().size() == 3);

	srv.modifica(2, "aaa", "bbb", 4, "ccc");
	assert(srv.getAll().size() == 3);
	srv.undo();

	try
	{
		repo.getFilmById(10);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
}
void testeExport()
{
	Repository repo;
	Validator val;
	Service srv{ repo,val };
	srv.adauga("TheHobbit", "adventure", 2000, "Dan");
	srv.adauga("Inferno", "action", 2006, "Marius");
	srv.adauga("Centrale", "drama", 2002, "Andrei");
	srv.adauga("Musica", "drama", 2000, "Adriana");
	string fisier = "test.cvs";
	srv.addToCos("Inferno");
	srv.exportaCosCVS(fisier);
	std::ifstream fin(fisier);
	assert(fin.is_open());
	int linii = 0;
	string linie;
	while (std::getline(fin, linie))
		++linii;
	//std::cout << linii;
	assert(linii == 1);

	string fisier2 = "test.html";
	srv.exportaCosHTML(fisier2);
	std::ifstream fin2(fisier2);
	assert(fin2.is_open());
	linii = 0;
	while (std::getline(fin2, linie))
		++linii;

	assert(linii == 10);

}
void testeMap()
{
	MapRepo map{ 0.0 };
	map.adauga(Film{ "aaaa","bbbb",1990,"cccc" });
	assert(map.getAll().size() == 1);

	map.adauga(Film{ "ffff","ggg",2000,"rrr" });

	map.sterge(1);
	assert(map.getAll().size() == 1);
	map.adauga(Film{ "ffff","ggg",2000,"rrr" });
	map.modifica(1, Film{ "ffff","ggg",2000,"rrr" });
	map.sterge(0);
	map.adauga(Film{ "aaaa","bbbb",1990,"cccc" });

	auto titluF = map.existaTitlu("aaaa");
	assert(titluF.getAn() == 1990);
	try
	{
		auto f = map.existaTitlu("Film");
	}
	catch (RepositoryException&)
	{
		assert(true);
	}
	auto film = map.getFilmById(0);
	assert(film.getAn() == 1990);

	try
	{
		film = map.getFilmById(10);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	int poz;
	try
	{
		poz = map.findId(10);
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	//getId
	auto poz2 = map.getId(Film{ "aaaa","bbbb",1990,"cccc" });
	assert(poz2 == 0);
	try
	{
		poz2 = map.getId(Film{ "a","b",199,"cc" });
	}
	catch (RepositoryException&)
	{
		assert(true);
	}

	MapRepo repo2{ 1.0 };
	try
	{
		repo2.adauga(Film{ "a","b",1990,"c" });
	}
	catch (ProbilitateException& ex)
	{
		cout << ex << endl;
		assert(true);
	}
}
void testeRepoFile()
{

	//Repository repo;
	//clear the file
	std::ofstream ofs("testRepo.txt", std::ios::trunc);
	ofs.close();
	RepoFile repoFile{ "testRepo.txt" };
	//ofs.open("testRepo.txt", ios::out | ios::trunc);
	//ofs.close();

	repoFile.adauga(Film{ "mv1","gen1",2000,"act1" });
	RepoFile repoFile2{ "testRepo.txt" };
	repoFile2.modifica(0, Film{ "mv2","gen2",2002,"act2" });
	repoFile2.sterge(0);


	//assert(fin.is_open());
	/*
	int linii = 0;
	string linie;
	while (std::getline(fin, linie))
		++linii;
	//std::cout << linii;
	assert(linii == 4);
	*/
	/*
	repoFile.modifica(0, Film{ "mv2","gen2",2002,"act2" });
	repoFile.sterge(0);
	linii = 0;
	while (std::getline(fin, linie))
		++linii;

	//assert(linii == 0);
	*/
}
