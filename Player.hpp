#ifndef _PLAYER_H
#define _PLAYER_H

#include <QObject>
#include <QString>
#include "GameBoard.hpp"

class Player : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString someVar READ someVar WRITE setSomeVar NOTIFY someVarChanged)
public:
    explicit Player(QObject *parent = nullptr);
    QString someVar();
    Q_INVOKABLE QString getSomeVar();
    Q_INVOKABLE void setSomeVar(const QString &someVar);

signals:
    void someVarChanged(const QString &someVar);

public slots:

private:
    QString m_someVar;

};
#endif
