#pragma once
#include <vector>
#include "Domain.h"
#include "Observer.h"
class Cos: public Observable
{
private:
	vector<Film> cos_inchirieri;
public:
	Cos() = default;

	const size_t cos_lungime() noexcept;

	void cos_add(const Film& film);
	void cos_fill(int nr, vector<Film> filme);
	Film cos_search(string titlu);
	void cos_reset();
	const vector<Film>& cos_get() noexcept;
};