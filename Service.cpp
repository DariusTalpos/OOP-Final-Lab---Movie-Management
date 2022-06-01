#include "Service.h"
#include <fstream>
#include <random>
#include <vector>
#include <unordered_map>

#include <iostream>
using namespace std;

const size_t Service::service_lungime() noexcept
{
	return this->filerepository.repo_lungime();
}

const size_t Service::service_lungime_cos() noexcept
{
	return this->cos.cos_lungime();
}

void Service::service_add(string titlu, string gen, string actor_principal, string an_aparitie)
{
	int an = transformare_string_numar(an_aparitie);
	Film film(titlu, gen, actor_principal, an);
	validator.validare_film(film);
	validator.validare_exista_film(film, filerepository.repo_get());
	filerepository.repo_add(film);
	undo_list.push_back(new UndoAdauga(filerepository));
}

void Service::service_add_cos(string titlu)
{
	Film film = service_search(titlu);
	validator.validare_rezultat_cautare(film);
	cos.cos_add(film);
}

void Service::service_fill_cos(string numar)
{
	int const nr = transformare_string_numar(numar);
	validator.validare_fill(nr);
	cos.cos_fill(nr, filerepository.repo_get());
}

void Service::service_modify(string titlu, string gen, string actor_principal, string an_aparitie, string pozitie)
{
	int poz = transformare_string_numar(pozitie);
	int const an = transformare_string_numar(an_aparitie);
	Film film(titlu, gen, actor_principal, an);
	validator.validare_pozitie(poz, filerepository.repo_lungime());
	poz--;
	validator.validare_film(film);
	Film f = filerepository.repo_get_pozitie(poz);
	undo_list.push_back(new UndoModifica(poz, f, filerepository));
	filerepository.repo_modify(film, poz);
}

void Service::service_delete(string pozitie)
{
	int poz = transformare_string_numar(pozitie);
	validator.validare_pozitie(poz, filerepository.repo_lungime());
	poz--;
	Film f = filerepository.repo_get_pozitie(poz);
	undo_list.push_back(new UndoSterge(poz, f, filerepository));
	this->filerepository.repo_delete(poz);
}

Film Service::service_search(string titlu)
{
	return this->filerepository.repo_search(titlu);
}

vector<Film> Service::service_filter(string proprietate, string obiect)
{
	validator.validator_fisier(obiect);
	validator.validare_proprietate1(proprietate);
	if (proprietate == "1")
	{
		vector<Film> rez = filerepository.repo_filter_titlu("1", obiect);
		validator.validator_titlu(static_cast<int>(rez.size()));
		return filerepository.repo_filter_titlu("1", obiect);
	}
	else if (proprietate == "2")
		return filerepository.repo_filter_titlu("2", obiect);
	else if (proprietate == "3")
		return filerepository.repo_filter_an("1", transformare_string_numar(obiect));
	return filerepository.repo_filter_an("2", transformare_string_numar(obiect));
}

vector<Film> Service::service_sort(string proprietate, string ordine)
{
	validator.validare_proprietate_ordine(proprietate, ordine);
	vector<Film> rezultat;
	if (proprietate == "titlu")
	{
		if (ordine == "crescator")
			rezultat = filerepository.repo_sort(cmpTitluCrescator);
		else
			rezultat = filerepository.repo_sort(cmpTitluDescrescator);
	}
	if (proprietate == "actor")
	{
		if (ordine == "crescator")
			rezultat = filerepository.repo_sort(cmpActorCrescator);
		else
			rezultat = filerepository.repo_sort(cmpActorDescrescator);
	}
	if (proprietate == "an+gen")
	{
		if (ordine == "crescator")
			rezultat = filerepository.repo_sort(cmpAnGenCrescator);
		else
			rezultat = filerepository.repo_sort(cmpAnGenDescrescator);
	}
	return rezultat;
}

const vector<Film>& Service::service_get() noexcept
{
	return this->filerepository.repo_get();
}

const vector<Film>& Service::service_get_cos() noexcept
{
	return this->cos.cos_get();
}

void Service::service_reset()
{
	while (undo_list.size() != 0)
		service_undo();
	this->filerepository.repo_reset();
}

void Service::service_reset_cos()
{
	validator.validare_pozitie(1, service_lungime_cos());
	this->cos.cos_reset();
}

unordered_map<string, int> Service::service_raport()
{
	unordered_map<string, int> map;
	vector<Film> filme = filerepository.repo_get();
	for (Film film : filme)
		map[film.getGen()]++;
	return map;
}

void Service::service_export(string fisier, vector<Film> date)
{
	validator.validator_fisier(fisier);
	//filerepository.store_to_file(fisier, date);
}

void Service::service_undo()
{
	validator.validare_undo(undo_list);
	ActiuneUndo* au = undo_list.back();
	au->doUndo();
	undo_list.pop_back();
	delete au;
}

void Service::service_load()
{
	//vector<Film> lista = filerepository.load_from_file("inserare.txt");
	
}

int transformare_string_numar(string str)
{
	int numar = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str.at(i) > 57 || str.at(i) < 48)
			return -1;
		else
			numar = numar * 10 + (str.at(i) - '0');
	}
	return numar;
}
