#include "Domain.h"

Film::Film(string titlu, string gen, string actor_principal, int an_aparitie)
{
	this->titlu = titlu;
	this->gen = gen;
	this->actor_principal = actor_principal;
	this->an_aparitie = an_aparitie;
}

string Film::getTitlu() const
{
	return this->titlu;
}

string Film::getGen() const
{
	return this->gen;
}

string Film::getActor() const
{
	return this->actor_principal;
}

int Film::getAn() const noexcept
{
	return this->an_aparitie;
}

void Film::setTitlu(string titlu_nou)
{
	this->titlu = titlu_nou;
}

void Film::setGen(string gen_nou)
{

	this->gen = gen_nou;
}

void Film::setActor(string actor_principal_nou)
{
	this->actor_principal = actor_principal_nou;
}

void Film::setAn(int an_aparitie_nou) noexcept
{
	this->an_aparitie = an_aparitie_nou;
}

bool cmpTitluCrescator(const Film& f1, const Film& f2)
{
	return f1.getTitlu() < f2.getTitlu();
}

bool cmpTitluDescrescator(const Film& f1, const Film& f2)
{
	return f1.getTitlu() > f2.getTitlu();
}

bool cmpActorCrescator(const Film& f1, const Film& f2)
{
	return f1.getActor() < f2.getActor();
}

bool cmpActorDescrescator(const Film& f1, const Film& f2)
{
	return f1.getActor() > f2.getActor();
}

bool cmpAnGenCrescator(const Film& f1, const Film& f2)
{
	if (f1.getAn() != f2.getAn())
		return f1.getAn() < f2.getAn();
	else
		return f1.getGen() < f2.getGen();
}

bool cmpAnGenDescrescator(const Film& f1, const Film& f2)
{
	if (f1.getAn() != f2.getAn())
		return f1.getAn() > f2.getAn();
	else
		return f1.getGen() > f2.getGen();
}