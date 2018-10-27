#include <fstream>
#include <string>
#include <vector>
#include "Film.h"
#include "Export.h"

void exportToCVS(const std::string &fileName, const std::vector<Film>&filme)
{
	std::ofstream fout(fileName, std::ios::trunc);
	/*
	if (!fout.is_open())
	{
		throw std::exception("Nu se poate deschide fisierul\n");
	}
	*/
	for (const auto&f : filme)
	{
		fout << f.getTitlu() << ",";
		fout << f.getGen() << ",";
		fout << f.getAn() << ",";
		fout << f.getActor() << "\n";
	}
	fout.close();
}

void exportToHTML(const std::string &fileName, const std::vector<Film>&filme)
{
	std::ofstream fout(fileName, std::ios::trunc);
	/*
	if (!fout.is_open())
	{
		throw std::exception("Nu se poate deschide fisierul\n");
	}
	*/
	fout << "<html><body>" << std::endl;
	fout << "<table border=\"1\" style=\"width:100% \">" << std::endl;
	for (const auto&f : filme)
	{
		fout << "<tr>" << std::endl;
		fout << "<td>" << f.getTitlu() << "</td>" << std::endl;
		fout << "<td>" << f.getGen() << "</td>" << std::endl;
		fout << "<td>" << f.getAn() << "</td>" << std::endl;
		fout << "<td>" << f.getActor() << "</td>" << std::endl;
		fout << "</tr>" << std::endl;
	}
	fout << "</table>" << std::endl;
	fout << "</body></html>" << std::endl;
	fout.close();
}