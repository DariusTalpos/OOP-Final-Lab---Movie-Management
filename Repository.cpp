#include "Repository.h"

#include <algorithm>
#include <fstream>

using namespace std;

const vector<Film>& Repository::repo_get() noexcept
{
	return this->lista_filme;
}

const Film& Repository::repo_get_pozitie(int pozitie)
{
	return this->lista_filme.at(pozitie);
}

const size_t Repository::repo_lungime() noexcept
{
	return this->lista_filme.size();
}

void Repository::repo_add(const Film& film)
{
	lista_filme.push_back(film);
}

void Repository::repo_modify(const Film& film, int pozitie)
{
	lista_filme.at(pozitie).setActor(film.getActor());
	lista_filme.at(pozitie).setAn(film.getAn());
	lista_filme.at(pozitie).setGen(film.getGen());
	lista_filme.at(pozitie).setTitlu(film.getTitlu());
}

void Repository::repo_delete(size_t pozitie)
{
	lista_filme.erase(lista_filme.begin() + pozitie);
}

Film Repository::repo_search(string titlu)
{
	auto acelasi_titlu = [=](Film film) { return film.getTitlu() == titlu; };
	vector<Film>::iterator it;
	it = find_if(lista_filme.begin(), lista_filme.end(), acelasi_titlu);
	if (it != lista_filme.end())
		return *it;
	Film film("", "", "", 0);
	return film;
}

vector<Film> Repository::repo_filter_titlu(string modalitate, string titlu)
{
	vector<Film> rezultat;
	if (modalitate == "1")
	{
		copy_if(lista_filme.begin(), lista_filme.end(), back_inserter(rezultat), [=](Film f) {return f.getTitlu() == titlu; });
	}
	else
	{
		copy_if(lista_filme.begin(), lista_filme.end(), back_inserter(rezultat), [=](Film f) {return f.getTitlu() != titlu; });
	}
	return rezultat;

}

vector<Film> Repository::repo_filter_an(string modalitate, int an)
{
	vector<Film> rezultat;
	if (modalitate == "1")
	{
		copy_if(lista_filme.begin(), lista_filme.end(), back_inserter(rezultat), [=](Film f) {return f.getAn() <= an; });
	}
	else
	{
		copy_if(lista_filme.begin(), lista_filme.end(), back_inserter(rezultat), [=](Film f) {return f.getAn() > an; });
	}
	return rezultat;
}

vector<Film> Repository::repo_sort(bool(*f_cmp)(const Film&, const Film&))
{
	vector<Film> filme = repo_get();
	sort(filme.begin(), filme.end(), f_cmp);
	return filme;
}

void Repository::repo_reset() noexcept
{
	lista_filme.erase(lista_filme.begin(), lista_filme.end());
}

void Repository::repo_insert(int pozitie, Film film)
{
	lista_filme.push_back(Film("", "", "", 0));
	for (size_t i = lista_filme.size() - 1; i > pozitie; i--)
		lista_filme.at(i) = lista_filme.at(i - 1);
	lista_filme.at(pozitie) = film;
}

// ---------------------------------------------------------------------

void FileRepository::store_to_file(string nume_fisier, vector<Film> lista)
{
	ofstream fout(nume_fisier);
	for (int i = 0; i < lista.size(); i++)
		fout << lista.at(i).getTitlu() << "," << lista.at(i).getGen() << "," << lista.at(i).getAn() << "," << lista.at(i).getActor() << '\n';
	fout.close();
}

void FileRepository::load_from_file(string nume_fisier)
{
	lista_filme.clear();
	ifstream fin(nume_fisier);
	const string separator = ",";
	string rand;
	while (getline(fin, rand, '\n'))
	{
		if (rand.empty())
			continue;
		string obiecte[4];
		size_t pos = 0;
		int i = 0;

		while ((pos = rand.find(separator)) != string::npos)
		{
			obiecte[i++] = rand.substr(0, pos);
			rand.erase(0, pos + separator.length());
		}
		obiecte[i] = rand.substr(0, pos - 1);
		const string Titlu = obiecte[0];
		const string Gen = obiecte[1];
		const int An = stoi(obiecte[2]);
		const string Actor = obiecte[3];

		const Film f = Film(Titlu, Gen, Actor, An);

		Repository::repo_add(f);
	}
	fin.close();
} 