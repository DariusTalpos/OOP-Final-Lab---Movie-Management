#pragma once
#include <string>
#include <iostream>
using namespace std;

class Film
{
private:
	string titlu;
	string gen;
	string actor_principal;
	int an_aparitie=0;

public:
	Film() = default;
	/*
	* Iterator pentru film
	*/
	Film(string titlu, string gen, string actor_principal, int an_aparitie);
	/*
	* Functie de copiere pentru film
	*/
	Film(const Film& original) : titlu{ original.titlu }, gen{ original.gen }, actor_principal{ original.actor_principal }, an_aparitie{ original.an_aparitie }{ //cout << "\nA copy has taken place.\n"; 
	}
	Film(Film&&) = default;
	Film& operator=(const Film&) = default;
	Film& operator=(Film&&) = default;
	~Film() = default;

	string getTitlu() const;
	string getGen() const;
	string getActor() const;
	int getAn() const noexcept;

	void setTitlu(string titlu);
	void setGen(string gen);
	void setActor(string actor_principal);
	void setAn(int an_aparitie) noexcept;
};


bool cmpTitluCrescator(const Film& f1, const Film& f2);

bool cmpTitluDescrescator(const Film& f1, const Film& f2);

bool cmpActorCrescator(const Film& f1, const Film& f2);

bool cmpActorDescrescator(const Film& f1, const Film& f2);

bool cmpAnGenCrescator(const Film& f1, const Film& f2);

bool cmpAnGenDescrescator(const Film& f1, const Film& f2);

