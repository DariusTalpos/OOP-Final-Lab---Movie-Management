#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Domain.h"
using std::vector;
class MyTableModel: public QAbstractTableModel
{
private:
	vector<Film> filme;
public:
	MyTableModel(vector<Film> f): filme{f}{};
	
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant header(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	
	void setElements(vector<Film> f);

};

