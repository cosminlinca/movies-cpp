#pragma once
template <typename Telement>
class Nod
{
public:
	Telement info; //informatie
	Nod *urm; //legatura
	Nod() noexcept;
	~Nod() = default;
};

template <typename Telement>
Nod<Telement>::Nod() noexcept
{
	urm = NULL;
}


