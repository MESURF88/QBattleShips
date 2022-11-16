#ifndef _DISPLAY_LOGIC_H
#define _DISPLAY_LOGIC_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "GameBoardTest.hpp"

class DisplayLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString someVar READ someVar WRITE setSomeVar NOTIFY someVarChanged)
    Q_PROPERTY(GameBoardTest* listInitiator READ listInitiator NOTIFY listInitiatorChanged)
    Q_PROPERTY(GameBoardTest* listInitiated READ listInitiated NOTIFY listInitiatedChanged)
public:
    explicit DisplayLogic(QObject *parent = nullptr);
    Q_INVOKABLE void startGame();
    QString someVar();
    Q_INVOKABLE QString getSomeVar();
    Q_INVOKABLE void setSomeVar(const QString &someVar);
    GameBoardTest* listInitiator();
    GameBoardTest* listInitiated();

signals:
    void someVarChanged(const QString &someVar);
    void listInitiatorChanged();
    void listInitiatedChanged();

public slots:
    void processTheMove();
protected:
    GameBoardTest _battleShipInitiator;
    GameBoardTest _battleShipInitiated;
private:

    QString m_someVar;
    QTimer *m_timer = nullptr;


};
#endif
