#include "MyListModel.h"

int MyListModel::rowCount(const QModelIndex& /*parent*/) const
{
	return static_cast<int>(filme.size());
}
int MyListModel::columnCount(const QModelIndex& /*parent*/) const
{
	return 1;
}
QVariant MyListModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		//return QString("Row%1, Column%2").arg(index.row() + 1).arg(index.column() + 1);
		string film = filme[index.row()].getTitlu();
		return QString("%1").arg(QString::fromStdString(film));

	}
	else
		if (role == Qt::UserRole)
			return QString::fromStdString(filme[index.row()].getTitlu());
	return QVariant();
}

void MyListModel::setElements(vector<Film> f)
{
	filme = f;
	auto topLeft = createIndex(0, 0);
	auto botRight = createIndex(rowCount(), 0);
	
	QModelIndex index;
	string film;

	for (int i = 0; i < filme.size(); i++)
	{
		index = createIndex(i, 0);
		film = filme[index.row()].getTitlu();
		setData(index, QString::fromStdString(film), Qt::UserRole);
		QString dataGot = data(index, Qt::UserRole).toString();
	}

	emit dataChanged(topLeft, botRight);
}