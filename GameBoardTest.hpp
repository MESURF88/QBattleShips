#ifndef _GAMEBOARDTEST_H
#define _GAMEBOARDTEST_H

#include <QObject>
#include <QString>
#include <QModelIndex>
#include "Ship.hpp"
#include <QDebug>//TODO: KJH

static constexpr uint NUMBATTLESHIPS = 1;
static constexpr uint BATTLESHIPLEN = 4;
static constexpr uint NUMCRUISERS = 2;
static constexpr uint CRUISERLEN = 3;
static constexpr uint NUMDESTROYERS = 3;
static constexpr uint DESTROYERLEN = 2;
static constexpr uint NUMSUBMARINES = 4;
static constexpr uint SUBMARINELEN = 1;

class BoardTileTest
{
 public :
    BoardTileTest(const QString& name, const QString& color)
    {
        mName = name;
        mColor = color;
    };

    BoardTileTest()
    {
        mName = "Water";
        mColor = "blue";
    };

    QString BoardTileTest::getName() const{
        return mName;
    }
    QString BoardTileTest::getColor() const{
        return mColor;
    }
 private:

    QString mName;
    QString mColor;
};

class GameBoardTest : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        NameRole = Qt::UserRole,
        TcolorRole
    };

public:
    explicit GameBoardTest(QObject *parent = 0);
    
	int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;
    void modifyIndex(int index, BoardTileTest changeTo);
    void modifyCoord(uint x, uint y, BoardTileTest changeTo);
    int getShipSpaces() const;
    void shotAt();
signals:
    void someVarChanged(const QString &someVar);

public slots:

private:
    QVector<BoardTileTest> m_data;
    QVector<Ship> m_ships;

    void findPlaceShip(uint *xref, uint *yref, Direction *dir, int length);
    void placeShip(uint *xref, uint *yref, Direction *dir, QString name, int length);
    int flatIndexer(uint x, uint y);
    void arrayIndexer(int index, uint *x, uint *y);
    bool overlapDetected(uint x, uint y);
    bool randomFlipper();

};
#endif
