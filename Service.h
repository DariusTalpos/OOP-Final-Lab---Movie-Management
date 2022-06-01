#pragma once
#include "Repository.h"
#include "Validare.h"
#include "Undo.h"
#include "Cos.h"
#include <unordered_map>
class Service
{
private:

	//Repository& repository;
	FileRepository& filerepository;
	Cos& cos;
	ValidatorFilme& validator;
	vector<ActiuneUndo*> undo_list;

public:
	/*
	* Constructor pentru service
	* @repository - referinta la obiect de tip Repository
	* @validator - referinta la obiect de tip ValidatorFilme
	*/
	Service(FileRepository& filerepository, Cos& cos, ValidatorFilme& validator) noexcept : filerepository{ filerepository }, cos{ cos }, validator{ validator } {};
	/*
	* Preia din repo lungimea vectorului de filme
	*/
	const size_t service_lungime() noexcept;
	const size_t service_lungime_cos() noexcept;
	/*
	* Valideaza datele si, daca acestea sunt corecte, apeleaza repository pentru adaugarea filmului in vector
	*/
	void service_add(string titlu, string gen, string actor_principal, string an_aparitie);
	/*
	* Valideaza datele si, daca acestea sunt corecte, apeleaza repository pentru modificarea filmului de pe pozitia data
	*/
	void service_modify(string titlu, string gen, string actor_principal, string an_aparitie, string pozitie);
	/*
	* Sterge filmul de pe pozitia data
	*/
	void service_delete(string pozitie);
	/*
	* Apeleaza repository-ul pentru a cauta filmul cu titlul si actorul corespunzator
	* Returneaza:
	*			  filmul, daca este gasit
	* un film care are campuri goale, altfel
	*/
	Film service_search(string titlu);

	vector<Film> service_filter(string proprietate, string obiect);

	vector<Film> service_sort(string proprietate, string ordine);

	void service_add_cos(string titlu);
	/*
	* Preia din repository lista de filme
	*/
	void service_fill_cos(string numar);

	unordered_map<string, int> service_raport();

	void service_export(string fisier, vector<Film> date);

	void service_undo();

	const vector<Film>& service_get() noexcept;
	const vector<Film>& service_get_cos() noexcept;
	/*
	* reseteaza vectorul din repository(pentru filme)
	*/
	void service_reset();
	void service_reset_cos();

	void service_load();
};


int transformare_string_numar(string str);
