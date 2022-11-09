#ifndef _GAMEBOARDTEST_H
#define _GAMEBOARDTEST_H

#include <QObject>
#include <QString>
#include <QModelIndex>
#include <QDebug>//TODO: KJH

class BoardTileTest
{
 public :
    BoardTileTest() {};
    BoardTileTest(const QString& name, const int& x, const int& y)
    {
        mName = name;
        mX = x;
        mY = y;
    };
    QString BoardTileTest::getName() const{
        return mName;
    }
 private:

    QString mName;
    int mX;
    int mY;
};

class GameBoardTest : public QAbstractListModel
{
    Q_OBJECT

    enum Roles
    {
        NameRole = Qt::UserRole,
        AgeRole
    };

public:
    explicit GameBoardTest(QObject *parent = 0);
    
	int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;
signals:
    void someVarChanged(const QString &someVar);

public slots:

private:
    QVector<BoardTileTest> m_data;

};
#endif
