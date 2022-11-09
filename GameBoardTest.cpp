#include "GameBoardTest.hpp"
#include "QRandomGenerator"

GameBoardTest::GameBoardTest(QObject *parent): QAbstractListModel(parent)
{

    qDebug() << "built";
    beginResetModel();
    for (int i = 0; i < 100; i++)
    {
        quint32 t = QRandomGenerator::global()->generate();
        if (t % 2 == 0)
            m_data.append(BoardTileTest("ShipOne", 1, 1));
        else
            m_data.append(BoardTileTest("ShipTwo", 1, 1));
    }
    endResetModel();
}

int GameBoardTest::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return 0;
	
	return m_data.count();
}

QVariant GameBoardTest::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
     switch (role) {
         case Qt::DisplayRole:
         case NameRole:
         //qDebug() << "string: " << m_data.at(index.row()).getName();
             return QVariant(m_data.at(index.row()).getName());
     }
    return QVariant();
}

QHash<int, QByteArray> GameBoardTest::roleNames() const
{
	static QHash<int, QByteArray> mapping {
        {NameRole, "name"}
	};
	return mapping;
}
