#include "GameBoard.hpp"

GameBoard::GameBoard(QObject *parent)
{

}

int GameBoard::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return 0;
	
	return m_data.count();
}

QVariant GameBoard::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

    return QVariant();
}

QHash<int, QByteArray> GameBoard::roleNames() const
{
	static QHash<int, QByteArray> mapping {
		
	};
	
	return mapping;
}
