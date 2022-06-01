#pragma once
#include <QAbstractListModel>
#include <vector>
#include <string>
#include "Domain.h"
using std::vector;
class MyListModel: public QAbstractListModel
{
private:
	vector<Film> filme;
public:
	MyListModel(vector<Film> f) : filme{ f } {};

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	void setElements(vector<Film> f);
};

