#pragma once
#include <QtWidgets\qlistwidget.h>
#include <Film.h>

class QMListWidgetItem : public QListWidgetItem
{
public:
	QMListWidgetItem(const std::pair<int, Film>& film) : film{ film } {}
	std::pair<int, Film> getFilm();
private:
	std::pair<int, Film> film;
};