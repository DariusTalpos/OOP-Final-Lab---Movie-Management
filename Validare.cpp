#pragma once
#include "Validare.h"

ValidatorExceptii::ValidatorExceptii(vector<string> erori)
{
	this->erori = erori;
}

string ValidatorExceptii::getErori()
{
	string mesaj = "";
	for (const string eroare : erori)
		mesaj += eroare + "\n";
	return mesaj;
}

void ValidatorFilme::validare_film(const Film& film)
{
	vector<string> erori;
	if (film.getTitlu().length() < 2)
		erori.push_back("Titlul filmului trebuie sa aiba minim doua caractere.");
	if (film.getGen().length() < 2)
		erori.push_back("Genul filmului trebuie sa aiba minim doua caractere.");
	if (film.getActor().length() < 2)
		erori.push_back("Actorul filmului trebuie sa aiba minim doua caractere.");
	if (film.getAn() < 1900 || film.getAn() > 2050)
		erori.push_back("Filmul trebuie sa fi aparut intr-un an realist...");

	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_exista_film(const Film& film, vector<Film> filme)
{
	vector<string> erori;
	string t = film.getTitlu();

	if (!filme.empty())
	{
		auto acelasi_titlu = [=](Film film) { return film.getTitlu() == t; };
		vector<Film>::iterator it;
		it = find_if(filme.begin(), filme.end(), acelasi_titlu);

		if (it != filme.end())
			erori.push_back("Filmul exista deja!");
		if (erori.size() > 0)
			throw ValidatorExceptii(erori);
	}
}

void ValidatorFilme::validare_rezultat_cautare(const Film& film)
{
	vector<string> erori;
	if (film.getTitlu().length() < 2)
		erori.push_back("Nu exista film care sa aiba acest titlu.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_pozitie(size_t poz, const size_t pozitii)
{
	vector<string> erori;
	if (pozitii <= 0)
		erori.push_back("Lista este goala");
	if (poz > pozitii || poz - 1 < 0)
		erori.push_back("Numar incorect.");

	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_proprietate1(const string proprietate)
{
	vector<string> erori;
	if (proprietate < "1" || proprietate > "4")
		erori.push_back("Proprietate incorecta.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_proprietate_ordine(const string proprietate, const string ordine)
{
	vector<string> erori;
	if (proprietate != "titlu" && proprietate != "actor" && proprietate != "an+gen")
		erori.push_back("Proprietate incorecta.");
	if (ordine != "crescator" && ordine != "descrescator")
		erori.push_back("Ordine incorecta.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_undo(vector<ActiuneUndo*> v)
{
	vector<string> erori;
	if (v.empty())
		erori.push_back("Nu exista operatii la care sa se efectueze undo.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validare_fill(int nr)
{
	vector<string> erori;
	if (nr <= 0)
		erori.push_back("Numarul este incorect.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validator_fisier(string fisier)
{
	vector<string> erori;
	if(fisier=="")
		erori.push_back("Nu a fost completat campul necesar.");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

void ValidatorFilme::validator_titlu(int dim)
{
	vector<string> erori;
	if (dim==0)
		erori.push_back("Nu exista filmul cu acest nume");
	if (erori.size() > 0)
		throw ValidatorExceptii(erori);
}

