#pragma once
#include "Service.h"
class Teste
{
private:
	Service& service;
	Repository& direct_repository;
	FileRepository& direct_fr;
	Cos& direct_cos;
public:
	Teste(Service& service, Repository& direct_repository, FileRepository& direct_fr, Cos& direct_cos) noexcept : service{ service }, direct_repository{ direct_repository }, direct_fr{ direct_fr }, direct_cos{ direct_cos } {};
	void teste();
	void testeService();
	void testeRepository();
	void testeFileRepository();
	void testeCos();
	void testeDomain();

	void testServiceAddGet();
	void testServiceAddCos();
	void testServiceResetLungime() noexcept;
	void testServiceModify();
	void testServiceDelete();
	void testServiceSearch();
	void testServiceFilter();
	void testServiceSort();
	void testServiceFillCos();
	void testServiceRaport();
	void testServiceExport();
	void testServiceUndo();

	void testRepositoryAddGet();
	void testRepositoryResetLungime() noexcept;
	void testRepositoryModify();
	void testRepositoryDelete();
	void testRepositorySearch();
	void testRepositoryFilterTitlu();
	void testRepositoryFilterAn();
	void testRepositorySort();
	void testRepositoryInsert();

	void testFileRepositoryStore();

	void testCosAddGet();
	void testCosResetLungime();
	void testCosSearch();

	void testDomainGetSetTitlu();
	void testDomainGetSetGen();
	void testDomainGetSetActor();
	void testDomainGetSetAn();

	void testGetErori();
};
