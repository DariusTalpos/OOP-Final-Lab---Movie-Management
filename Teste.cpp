#include "Teste.h"
#include <assert.h>
#include <iostream>
#include <fstream>
using namespace std;

void Teste::teste()
{
	/*testeDomain();
	testeRepository();
	testeService();
	testeFileRepository();
	testeCos();
	testGetErori();*/
}

void Teste::testeDomain()
{
	testDomainGetSetActor();
	testDomainGetSetAn();
	testDomainGetSetGen();
	testDomainGetSetTitlu();
}

void Teste::testeRepository()
{
	testRepositoryAddGet();
	testRepositoryResetLungime();
	testRepositoryModify();
	testRepositoryDelete();
	testRepositorySearch();
	testRepositoryFilterTitlu();
	testRepositoryFilterAn();
	testRepositorySort();
	testRepositoryInsert();
}

void Teste::testeFileRepository()
{
	testFileRepositoryStore();
}

void Teste::testeCos()
{
	testCosAddGet();
	testCosResetLungime();
	testCosSearch();
}

void Teste::testeService()
{
	testServiceUndo();
	testServiceAddGet();
	testServiceAddCos();
	testServiceResetLungime();
	testServiceModify();
	testServiceDelete();
	testServiceSearch();
	testServiceFilter();
	testServiceSort();
	testServiceFillCos();
	//testServiceRaport();
	testServiceExport();
}

void Teste::testDomainGetSetActor()
{
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	assert(test.getActor() == "Keanu Reeves");
	test.setActor("Reanu Keeves");
	assert(test.getActor() == "Reanu Keeves");
}

void Teste::testDomainGetSetAn()
{
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	assert(test.getAn() == 2010);
	test.setAn(1984);
	assert(test.getAn() == 1984);
}

void Teste::testDomainGetSetGen()
{
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	assert(test.getGen() == "actiune");
	test.setGen("comedie romantica");
	assert(test.getGen() == "comedie romantica");
}

void Teste::testDomainGetSetTitlu()
{
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	assert(test.getTitlu() == "John Wick");
	test.setTitlu("Shrek");
	assert(test.getTitlu() == "Shrek");
}


void Teste::testRepositoryAddGet()
{
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	vector<Film> test_filme = direct_repository.repo_get();
	assert(test_filme.at(0).getTitlu() == "John Wick");
	assert(test_filme.at(0).getGen() == "actiune");
	assert(test_filme.at(0).getActor() == "Keanu Reeves");
	assert(test_filme.at(0).getAn() == 2010);
	Film rez = direct_repository.repo_get_pozitie(0);
	assert(rez.getTitlu() == "John Wick");
	assert(rez.getGen() == "actiune");
	assert(rez.getActor() == "Keanu Reeves");
	assert(rez.getAn() == 2010);
}


void Teste::testRepositoryResetLungime() noexcept
{
	size_t lungime = direct_repository.repo_lungime();
	assert(lungime == 1);
	direct_repository.repo_reset();
	lungime = direct_repository.repo_lungime();
	assert(lungime == 0);
}

void Teste::testRepositoryModify()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	Film test2("Shrek", "horror", "Will Smith", 1984);
	direct_repository.repo_modify(test2, 0);
	vector<Film> test_filme = direct_repository.repo_get();
	assert(test_filme.at(0).getTitlu() == "Shrek");
	assert(test_filme.at(0).getGen() == "horror");
	assert(test_filme.at(0).getActor() == "Will Smith");
	assert(test_filme.at(0).getAn() == 1984);
}

void Teste::testRepositoryDelete()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	Film test2("Shrek", "horror", "Will Smith", 1984);
	direct_repository.repo_add(test2);
	direct_repository.repo_delete(0);
	const size_t lungime = direct_repository.repo_lungime();
	assert(lungime == 1);
	vector<Film> test_filme = direct_repository.repo_get();
	assert(test_filme.at(0).getTitlu() == "Shrek");
	assert(test_filme.at(0).getGen() == "horror");
	assert(test_filme.at(0).getActor() == "Will Smith");
	assert(test_filme.at(0).getAn() == 1984);
}

void Teste::testRepositorySearch()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	Film rezultat = direct_repository.repo_search("John Wick");
	assert(rezultat.getTitlu() == "John Wick");
	assert(rezultat.getGen() == "actiune");
	assert(rezultat.getActor() == "Keanu Reeves");
	assert(rezultat.getAn() == 2010);
	rezultat = direct_repository.repo_search("Sonic 2");
	assert(rezultat.getTitlu() == "");
	assert(rezultat.getGen() == "");
	assert(rezultat.getActor() == "");
	assert(rezultat.getAn() == 0);
}

void Teste::testRepositoryFilterTitlu()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	vector<Film> rez = direct_repository.repo_filter_titlu("1", "John Wick");
	assert(rez.size() == 1);
	vector<Film> rez2 = direct_repository.repo_filter_titlu("2", "John Wick");
	assert(rez2.size() == 0);
	vector<Film> rez3 = direct_repository.repo_filter_titlu("1", "Shrek");
	assert(rez3.size() == 0);
	vector<Film> rez4 = direct_repository.repo_filter_titlu("2", "Shrek");
	assert(rez4.size() == 1);
}

void Teste::testRepositoryFilterAn()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	vector<Film> rez = direct_repository.repo_filter_an("1", 2030);
	assert(rez.size() == 1);
	vector<Film> rez2 = direct_repository.repo_filter_an("2", 2030);
	assert(rez2.size() == 0);
	vector<Film> rez3 = direct_repository.repo_filter_an("1", 2000);
	assert(rez3.size() == 0);
	vector<Film> rez4 = direct_repository.repo_filter_an("2", 2000);
	assert(rez4.size() == 1);
}

void Teste::testRepositorySort()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	Film test2("Sonic 2", "aventura", "Jim Carrey", 2020);
	direct_repository.repo_add(test2);
	vector<Film> sortat = direct_repository.repo_sort(cmpTitluCrescator);
	assert(sortat.size() == 2);

	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = direct_repository.repo_sort(cmpTitluDescrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	sortat = direct_repository.repo_sort(cmpActorCrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	sortat = direct_repository.repo_sort(cmpActorDescrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = direct_repository.repo_sort(cmpAnGenCrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = direct_repository.repo_sort(cmpAnGenDescrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	direct_repository.repo_reset();
	Film test3("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test3);
	Film test4("Sonic 2", "aventura", "Jim Carrey", 2010);
	direct_repository.repo_add(test4);

	sortat = direct_repository.repo_sort(cmpAnGenCrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2010);

	sortat = direct_repository.repo_sort(cmpAnGenDescrescator);
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

}

void Teste::testRepositoryInsert()
{
	direct_repository.repo_reset();
	Film test("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(test);
	Film test2("Sonic 2", "aventura", "Jim Carrey", 2020);
	direct_repository.repo_insert(0, test2);
	vector<Film> test_filme = direct_repository.repo_get();
	assert(direct_repository.repo_lungime() == 2);
	assert(test_filme.at(1).getTitlu() == "John Wick");
	assert(test_filme.at(1).getGen() == "actiune");
	assert(test_filme.at(1).getActor() == "Keanu Reeves");
	assert(test_filme.at(1).getAn() == 2010);
}

void Teste::testServiceAddGet()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	vector<Film> test_filme = service.service_get();
	assert(test_filme.at(0).getTitlu() == "John Wick");
	assert(test_filme.at(0).getGen() == "actiune");
	assert(test_filme.at(0).getActor() == "Keanu Reeves");
	assert(test_filme.at(0).getAn() == 2010);
	try
	{
		service.service_add("", "actiune", "Keanu Reeves", "2010");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "a", "Keanu Reeves", "2010");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "actiune", "K", "2010");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "actiune", "Keanu Reeves", "o suta");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "actiune", "Keanu Reeves", "5000");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "actiune", "Keanu Reeves", "150");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_add("John Wick", "actiune", "Keanu Reeves", "2022");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

void Teste::testServiceAddCos()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add_cos("John Wick");
	vector<Film> test_filme = service.service_get_cos();
	assert(test_filme.at(0).getTitlu() == "John Wick");
	assert(test_filme.at(0).getGen() == "actiune");
	assert(test_filme.at(0).getActor() == "Keanu Reeves");
	assert(test_filme.at(0).getAn() == 2010);
	try
	{
		service.service_add_cos("Matrix");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

void Teste::testServiceResetLungime() noexcept
{
	size_t lungime = service.service_lungime();
	assert(lungime == 1);
	service.service_reset();
	lungime = service.service_lungime();
	assert(lungime == 0);

	lungime = service.service_lungime_cos();
	assert(lungime == 1);
	service.service_reset_cos();
	lungime = service.service_lungime_cos();
	assert(lungime == 0);
}

void Teste::testServiceModify()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_modify("Shrek", "horror", "Will Smith", "1984", "1");
	vector<Film> test_filme = service.service_get();
	assert(test_filme.at(0).getTitlu() == "Shrek");
	assert(test_filme.at(0).getGen() == "horror");
	assert(test_filme.at(0).getActor() == "Will Smith");
	assert(test_filme.at(0).getAn() == 1984);
	try
	{
		service.service_modify("Sonic 3", "aventura", "Barrack Obama", "1977", "0");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_modify("", "aventura", "Barrack Obama", "1977", "1");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_modify("Sonic 3", "a", "Barrack Obama", "1977", "0");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_modify("Sonic 3", "aventura", "B", "1977", "0");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_modify("Sonic 3", "aventura", "Barrack Obama", "o mie", "0");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}


void Teste::testServiceDelete()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add("Shrek", "horror", "Will Smith", "1984");
	service.service_delete("1");
	const size_t lungime = service.service_lungime();
	assert(lungime == 1);
	vector<Film> test_filme = service.service_get();
	assert(test_filme.at(0).getTitlu() == "Shrek");
	assert(test_filme.at(0).getGen() == "horror");
	assert(test_filme.at(0).getActor() == "Will Smith");
	assert(test_filme.at(0).getAn() == 1984);
	try
	{
		service.service_delete("0");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		service.service_delete("3");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

void Teste::testServiceSearch()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	Film rezultat = service.service_search("John Wick");
	assert(rezultat.getTitlu() == "John Wick");
	assert(rezultat.getGen() == "actiune");
	assert(rezultat.getActor() == "Keanu Reeves");
	assert(rezultat.getAn() == 2010);
	rezultat = service.service_search("Sonic 2");
	assert(rezultat.getTitlu() == "");
	assert(rezultat.getGen() == "");
	assert(rezultat.getActor() == "");
	assert(rezultat.getAn() == 0);
}

void Teste::testServiceFilter()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	vector<Film> rez = service.service_filter("1", "John Wick");
	assert(rez.size() == 1);
	vector<Film> rez2 = service.service_filter("2", "John Wick");
	assert(rez2.size() == 0);
	vector<Film> rez3 = service.service_filter("1", "Shrek");
	assert(rez3.size() == 0);
	vector<Film> rez4 = service.service_filter("2", "Shrek");
	assert(rez4.size() == 1);
	vector<Film> rez5 = service.service_filter("3", "2030");
	assert(rez5.size() == 1);
	vector<Film> rez6 = service.service_filter("4", "2030");
	assert(rez6.size() == 0);
	vector<Film> rez7 = service.service_filter("3", "2000");
	assert(rez7.size() == 0);
	vector<Film> rez8 = service.service_filter("4", "2000");
	assert(rez8.size() == 1);

	try
	{
		rez = service.service_filter("a", "IDK");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		rez = service.service_filter("5", "2010");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

void Teste::testServiceSort()
{
	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add("Sonic 2", "aventura", "Jim Carrey", "2020");

	vector<Film> sortat = service.service_sort("titlu", "crescator");
	assert(sortat.size() == 2);

	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = service.service_sort("titlu", "descrescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	sortat = service.service_sort("actor", "crescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	sortat = service.service_sort("actor", "descrescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = service.service_sort("an+gen", "crescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2020);

	sortat = service.service_sort("an+gen", "descrescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2020);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	service.service_reset();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add("Sonic 2", "aventura", "Jim Carrey", "2010");

	sortat = service.service_sort("an+gen", "crescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "John Wick");
	assert(sortat.at(0).getGen() == "actiune");
	assert(sortat.at(0).getActor() == "Keanu Reeves");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "Sonic 2");
	assert(sortat.at(1).getGen() == "aventura");
	assert(sortat.at(1).getActor() == "Jim Carrey");
	assert(sortat.at(1).getAn() == 2010);

	sortat = service.service_sort("an+gen", "descrescator");
	assert(sortat.size() == 2);
	assert(sortat.at(0).getTitlu() == "Sonic 2");
	assert(sortat.at(0).getGen() == "aventura");
	assert(sortat.at(0).getActor() == "Jim Carrey");
	assert(sortat.at(0).getAn() == 2010);
	assert(sortat.at(1).getTitlu() == "John Wick");
	assert(sortat.at(1).getGen() == "actiune");
	assert(sortat.at(1).getActor() == "Keanu Reeves");
	assert(sortat.at(1).getAn() == 2010);

	try
	{
		sortat = service.service_sort("epic", "descrescator");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	try
	{
		sortat = service.service_sort("titlu", "cator");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

void Teste::testGetErori()
{
	service.service_reset();
	try
	{
		service.service_add("John Wick", "actiune", "Keanu Reeves", "5000");
	}
	catch (ValidatorExceptii& val)
	{
		assert(true);
		assert(val.getErori() == "Filmul trebuie sa fi aparut intr-un an realist...\n");
	}
}

void Teste::testServiceFillCos()
{
	service.service_reset();
	service.service_reset_cos();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add("Sonic 2", "aventura", "Jim Carrey", "2020");
	try
	{
		service.service_fill_cos("ab");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	service.service_fill_cos("2");
	assert(service.service_lungime_cos() == 2);
	try
	{
		service.service_fill_cos("1");
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
}

//void Teste::testServiceRaport()
//{
//	service.service_reset();
//	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
//	service.service_add("Sonic 2", "aventura", "Jim Carrey", "2022");
//	service.service_add("Batman", "actiune", "Joker", "2022");
//	unordered_map<int, int> rez = service.service_raport();
//	assert(rez.size() == 2);
//}

void Teste::testServiceExport()
{
	service.service_reset();
	service.service_reset_cos();
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_add("Sonic 2", "aventura", "Jim Carrey", "2022");
	service.service_add_cos("John Wick");
	service.service_export("epic.txt", service.service_get_cos());
	string fisier1("epic.txt");
	ifstream fin(fisier1);
	string rand1;
	getline(fin, rand1);
	assert(rand1 == "John Wick,actiune,2010,Keanu Reeves");
}

void Teste::testServiceUndo()
{
	service.service_reset();
	try
	{
		service.service_undo();
	}
	catch (ValidatorExceptii)
	{
		assert(true);
	}
	service.service_add("John Wick", "actiune", "Keanu Reeves", "2010");
	service.service_undo();
	size_t lungime = service.service_lungime();
	assert(lungime == 0);
	service.service_add("John Wick 2", "actiune", "Keanu Reeves", "2010");
	service.service_delete("1");
	service.service_undo();
	lungime = service.service_lungime();
	assert(lungime == 1);
	service.service_modify("ABC", "ABC", "ABC", "2022", "1");
	service.service_undo();
	vector<Film> test_filme = service.service_get();
	assert(test_filme.at(0).getTitlu() == "John Wick 2");
	assert(test_filme.at(0).getGen() == "actiune");
	assert(test_filme.at(0).getActor() == "Keanu Reeves");
	assert(test_filme.at(0).getAn() == 2010);

}

void Teste::testFileRepositoryStore()
{
	direct_repository.repo_reset();
	Film f("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_repository.repo_add(f);
	//direct_fr.store_to_file("test.txt", direct_repository.repo_get());
	//string fisier1("test.txt");
	//ifstream fin(fisier1);
	//string rand1;
	//getline(fin, rand1);
	//assert(rand1 == "John Wick,actiune,2010,Keanu Reeves");
}

void Teste::testCosAddGet()
{
	Film f("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_cos.cos_add(f);
	vector<Film>rez = direct_cos.cos_get();
	assert(rez.size() == 1);
	assert(rez.at(0).getTitlu() == "John Wick");
	assert(rez.at(0).getGen() == "actiune");
	assert(rez.at(0).getActor() == "Keanu Reeves");
	assert(rez.at(0).getAn() == 2010);
}

void Teste::testCosResetLungime()
{
	assert(direct_cos.cos_lungime() == 1);
	direct_cos.cos_reset();
	assert(direct_cos.cos_lungime() == 0);
}

void Teste::testCosSearch()
{
	direct_cos.cos_reset();
	Film f("John Wick", "actiune", "Keanu Reeves", 2010);
	direct_cos.cos_add(f);
	Film rez = direct_cos.cos_search("John Wick");
	assert(rez.getTitlu() == "John Wick");
	assert(rez.getGen() == "actiune");
	assert(rez.getActor() == "Keanu Reeves");
	assert(rez.getAn() == 2010);
	rez = direct_cos.cos_search("Sonic 2");
	assert(rez.getTitlu() == "");
	assert(rez.getGen() == "");
	assert(rez.getActor() == "");
	assert(rez.getAn() == 0);
}