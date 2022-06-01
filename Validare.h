#pragma once

#include "Domain.h"
#include "Undo.h"
#include <vector>
#include <string>
using namespace std;

class ValidatorExceptii {
private:
	vector<string> erori;
public:
	ValidatorExceptii(vector<string> erori);
	string getErori();
};

class ValidatorFilme
{
public:
	void validare_film(const Film& film);
	void validare_exista_film(const Film& film, vector<Film> filme);
	void validare_rezultat_cautare(const Film& film);
	void validare_pozitie(size_t poz, const size_t pozitii);
	void validare_proprietate1(const string proprietate);
	void validare_proprietate_ordine(const string proprietate, const string ordine);
	void validare_undo(vector<ActiuneUndo*> v);
	void validare_fill(int nr);
	void validator_fisier(string fisier);
	void validator_titlu(int dim);
};
