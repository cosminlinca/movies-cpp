#pragma once
#include "QMListWidgetItem.h"

std::pair<int, Film> QMListWidgetItem::getFilm()
{
	return this->film;
}