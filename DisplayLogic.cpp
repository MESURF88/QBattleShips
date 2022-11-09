#include "DisplayLogic.hpp"
#include "Player.hpp"
#include <QDebug>

DisplayLogic::DisplayLogic(QObject *parent) : QObject(parent)
{

}

void DisplayLogic::startGame()
{
    Player playerInitiator;
    Player playerInitiated;
    qDebug() << "test";
}

QString DisplayLogic::someVar()
{
    return m_someVar;
}

QString DisplayLogic::getSomeVar()
{
    return m_someVar;
}


void DisplayLogic::setSomeVar(const QString &someVar)
{
    if (someVar == m_someVar)
        return;
    m_someVar = someVar;
    emit someVarChanged(m_someVar);
}

GameBoardTest* DisplayLogic::listInitiator()
{
    return &_battleShipInitiator;
}

GameBoardTest* DisplayLogic::listInitiated()
{
    return &_battleShipInitiated;
}
