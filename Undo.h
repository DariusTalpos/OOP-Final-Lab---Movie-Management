#pragma once
#include "Repository.h"
#include <iostream>
using namespace std;
class ActiuneUndo
{
public:
	virtual ~ActiuneUndo() {};
	virtual void doUndo() = 0;
};

class UndoAdauga : public ActiuneUndo
{
private:
	Repository& repo;
public:
	UndoAdauga(Repository& repo) noexcept : repo{ repo } {};
	void doUndo() override
	{
		repo.repo_delete(repo.repo_lungime() - 1);
	}
};

class UndoSterge : public ActiuneUndo
{
private:
	int pozitie;
	Film filmSters;
	Repository& repo;
public:
	UndoSterge(int pozitie, Film filmSters, Repository& repo) : pozitie{ pozitie }, filmSters{ filmSters }, repo{ repo } {};
	void doUndo() override
	{
		repo.repo_insert(pozitie, filmSters);
	}
};

class UndoModifica : public ActiuneUndo
{
private:
	int pozitie;
	Film filmModificat;
	Repository& repo;
public:
	UndoModifica(int pozitie, Film filmModificat, Repository& repo) : pozitie{ pozitie }, filmModificat{ filmModificat }, repo{ repo } {};
	void doUndo() override
	{
		repo.repo_modify(filmModificat, pozitie);
	}
};
