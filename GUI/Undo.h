#pragma once
#include "Film.h"
#include "Repository.h"
class ActiuneUndo
{
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {}; //virtual destructor - se apeleaza destructorul pentru clasa potrivita
};

class UndoAdauga : public ActiuneUndo
{
	int idFilmAdaugat;
	AbstractRepo &repo;
public:
	UndoAdauga(AbstractRepo &repo, const int& id) : repo{ repo }, idFilmAdaugat{ id } {}
	void doUndo() override
	{
		repo.sterge(idFilmAdaugat);
	}
};

class UndoSterge : public ActiuneUndo
{
	Film filmSters;
	AbstractRepo &repo;
public:
	UndoSterge(AbstractRepo &repo, const Film& film) : repo{ repo }, filmSters{ film } {}
	void doUndo() override
	{
		repo.adauga(filmSters);
	}
};

class UndoUpdate : public ActiuneUndo
{
	int idFilmNou;
	Film filmVechi;
	AbstractRepo &repo;
public:
	UndoUpdate(AbstractRepo &repo, const int& id, const Film&film) : repo{ repo }, idFilmNou{ id }, filmVechi{ film } {}
	void doUndo() override
	{
		repo.sterge(idFilmNou);
		repo.adauga(filmVechi);
	}
};