#pragma once
#include <vector>
#include <algorithm>
#include <random>    // std::default_random_engine
#include <chrono>    // std::chrono::system_clock

#include "Film.h"
using std::vector;

class InchiriereCos
{
	vector<Film> Cos;
public:
	void adauga(const Film& f)
	{
		Cos.push_back(f);
	}
	void goleste()
	{
		Cos.clear();
	}
	void umpleAleator(size_t cate, vector<Film> all)
	{
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (Cos.size() < cate && all.size() > 0)
		{
			Cos.push_back(all.back());
			all.pop_back();
		}
	}
	const vector<Film>& lista() const
	{
		return Cos;
	}

};