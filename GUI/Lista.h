#pragma once
#include <stddef.h>
#include "Nod.h"

template <typename Telement>
class Iterator;

template <typename Telement>
class Lista
{
private:
	Nod<Telement> *prim;
public:
	friend class Iterator<Telement>;
	Lista() noexcept;
	~Lista(); //destructor

			  //Adauga un element in lista
	void adauga(Telement valoare);

	//Sterge un element din lista
	void sterge(int index) noexcept;

	void modifica(int index, Telement valoareNoua);

	//Returneaza lungimea listei
	int size() noexcept;

	//Interschimba informatia din doua noduri vecine(index, index+1)
	void swapInfo(int index);

	//Returneza informatia de la o pozitie din lista
	Telement getFromIndex(int);

	Iterator<Telement> iterator() const;

};
template <typename Telement>
Lista<Telement>::Lista() noexcept
{
	prim = NULL;
}
template <typename Telement>
Lista<Telement>::~Lista()
{
	while (this->prim != NULL)
	{
		auto nod = this->prim;
		this->prim = this->prim->urm;
		delete nod;
	}
}

template <typename Telement>
void Lista<Telement>::adauga(Telement valoare)
{
	if (prim == NULL)
	{
		auto nod = new Nod<Telement>;
		nod->info = valoare;
		nod->urm = NULL;
		prim = nod;
	}
	else
	{
		auto nod = prim;
		while (nod->urm != NULL)
			nod = nod->urm;

		auto q = new Nod <Telement>;
		q->info = valoare;
		q->urm = NULL;
		nod->urm = q;
	}
}
template <typename Telement>
void Lista<Telement>::sterge(int index) noexcept
{
	if (index == 0)
	{
		auto p = prim;
		prim = prim->urm;
		delete p;
		return;
	}
	Nod<Telement> *p = prim;
	index--;
	while (p->urm != NULL and index)
	{
		index--;
		p = p->urm;
	}
	Nod<Telement> *q = p->urm;
	p->urm = p->urm->urm;
	p = NULL;
	delete q;
}
template <typename Telement>
void Lista<Telement>::modifica(int index, Telement valoareNoua)
{
	auto p = prim;
	int c = 0;
	while (p != NULL and c != index)
	{
		c++;
		p = p->urm;
	}
	p->info = valoareNoua;
}

template <typename Telement>
int Lista<Telement>::size() noexcept
{
	int size = 0;
	auto nod = prim;
	while (nod != NULL)
	{
		nod = nod->urm;
		size++;
	}
	return size;
}

template <typename Telement>
void Lista<Telement>::swapInfo(int index)
{
	auto nod = prim;
	int c = 0;
	while (c != index && nod != NULL)
	{
		c++;
		nod = nod->urm;
	}
	Telement aux = nod->info;
	nod->info = nod->urm->info;
	nod->urm->info = aux;
}

template <typename Telement>
Telement Lista<Telement>::getFromIndex(int index)
{
	auto nod = prim;
	int c = 0;
	while (c != index && nod != NULL)
	{
		c++;
		nod = nod->urm;
	}
	return nod->info;
}

template <typename Telement>
Iterator<Telement> Lista<Telement>::iterator() const
{
	return Iterator(*this);
}


template <typename Telement>
class Iterator
{
	Iterator<Telement>(const Lista<Telement>&list);
	const Lista<Telement> &lista;
	Nod<Telement> *curent;
public:
	friend class Lista<Telement>;
	void prim();
	void urmator();
	bool valid() const;
	Telement element() const;
};

template <typename Telement>
Iterator<Telement>::Iterator(const Lista<Telement> &list) : lista(list)
{
	curent = list.prim;
}
template <typename Telement>
void Iterator<Telement>::prim()
{
	curent = lista.prim;
}
template <typename Telement>
void Iterator<Telement>::urmator()
{
	curent = curent->urm;
}
template <typename Telement>
bool Iterator<Telement>::valid() const {
	return curent != NULL;
}
template <typename Telement>
Telement Iterator<Telement>::element() const
{
	return curent->info;
}
