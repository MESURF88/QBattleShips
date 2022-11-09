#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <QObject>
#include <QModelIndex>

struct BoardTile {
	int x;
	int y;
};

class GameBoard : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit GameBoard(QObject *parent = nullptr);
    
	int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;
signals:
    void someVarChanged(const QString &someVar);

public slots:

private:
    QVector<int> m_data;

};
#endif
