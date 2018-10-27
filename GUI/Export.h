#pragma once
#include <vector>
#include "Film.h"
#include <string>

//in format Comma Separated Values
void exportToCVS(const std::string &fileName, const std::vector<Film>&filme);

//in format HTML
void exportToHTML(const std::string &fileName, const std::vector<Film>&filme);
