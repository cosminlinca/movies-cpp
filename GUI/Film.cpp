#include "Film.h"

Film::Film() noexcept
{
	this->an = 0;
}


Film::Film(const std::string& titlu, const std::string& gen, const int& an, const std::string& actor)
{
	this->titlu = titlu;
	this->gen = gen;
	this->an = an;
	this->actor = actor;
}
int Film::setTitlu(std::string t)
{
	this->titlu = t;
	return 0;
}
int Film::setGen(std::string g)
{
	this->gen = g;
	return 0;
}
int Film::setAn(int ann) noexcept
{
	this->an = ann;
	return 0;
}
int Film::setActor(std::string act)
{
	this->actor = act;
	return 0;
}
Film::~Film()
{
}
