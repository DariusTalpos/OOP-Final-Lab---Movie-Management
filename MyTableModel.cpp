#include "MyTableModel.h"

int MyTableModel::rowCount(const QModelIndex& /*parent*/) const
{
	return static_cast<int>(filme.size());
}
int MyTableModel::columnCount(const QModelIndex& /*parent*/) const
{
	return 2;
}
QVariant MyTableModel::data(const QModelIndex& index, int role) const 
{
	if (role == Qt::DisplayRole) {
		//return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() + 1);
		Film f = filme[index.row()];
		if (index.column() == 0)
			return QString::fromStdString(f.getTitlu());
		if (index.column() == 1)
			return QString::fromStdString(f.getActor());

	}
	return QVariant();
}

QVariant MyTableModel::header(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
			return QString("coloana %1").arg(section);
		else
			return QString("linia %1").arg(section);
	}
	return QVariant();
}

void MyTableModel::setElements(vector<Film> f)
{
	filme = f;
	auto topLeft = createIndex(0, 0);
	auto botRight = createIndex(rowCount(), columnCount());
	emit layoutChanged();
	emit dataChanged(topLeft, botRight);
}