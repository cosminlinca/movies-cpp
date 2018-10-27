#pragma once
#include "Film.h"
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qlineedit.h>
class MovieForm
{
private:
	QFormLayout *formlayout;
	QLineEdit* idEdit;
	QLineEdit* titluEdit;
	QLineEdit* genEdit;
	QLineEdit* anEdit;
	QLineEdit* actorEdit;

public:
	MovieForm();
	QFormLayout* getForm();
	Film getFilm();
	void clearData();
	void setData(const std::pair<int, Film>& film);

};