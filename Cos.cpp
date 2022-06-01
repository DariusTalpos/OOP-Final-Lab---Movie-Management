#include "Cos.h"

const size_t Cos::cos_lungime() noexcept
{
	return cos_inchirieri.size();
}

void Cos::cos_add(const Film& film)
{
	cos_inchirieri.push_back(film);
	notify();
}

void Cos::cos_fill(int nr, vector<Film> filme)
{
	for (int i = 1; i <= nr; i++)
	{
		Film f = filme[rand() % filme.size()];
		cos_add(f);
	}
	notify();
}

Film Cos::cos_search(string titlu)
{
	auto acelasi_titlu = [=](Film film) { return film.getTitlu() == titlu; };
	vector<Film>::iterator it;
	it = find_if(cos_inchirieri.begin(), cos_inchirieri.end(), acelasi_titlu);
	if (it != cos_inchirieri.end())
		return *it;
	Film film("", "", "", 0);
	return film;
}

const vector<Film>& Cos::cos_get() noexcept
{
	return cos_inchirieri;
}

void Cos::cos_reset()
{
	cos_inchirieri.erase(cos_inchirieri.begin(), cos_inchirieri.end());
	notify();
}