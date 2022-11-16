#include "DisplayLogic.hpp"
#include <QDebug>

DisplayLogic::DisplayLogic(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
}

void DisplayLogic::startGame()
{
    qDebug("started");

    connect(m_timer, SIGNAL(timeout()), this, SLOT(processTheMove()));
    m_timer->start(500);
}

void DisplayLogic::processTheMove()
{
    static int p1_turn = 1;
    if ((_battleShipInitiator.getShipSpaces() < 1) ||
        (_battleShipInitiated.getShipSpaces() < 1))
    {
        // find winner
        m_timer->stop();
        if (_battleShipInitiator.getShipSpaces() < _battleShipInitiated.getShipSpaces())
        {
            setSomeVar("Player 2 Wins! with " + QString::number(_battleShipInitiated.getShipSpaces()) + " spaces left");
        }
        else
        {
            setSomeVar("Player 1 Wins! with " + QString::number(_battleShipInitiator.getShipSpaces()) + " spaces left");
        }
    }
    else
    {
        if (p1_turn)
        {
            _battleShipInitiated.shotAt();
            p1_turn = 0;
        }
        else
        {
            _battleShipInitiator.shotAt();
            p1_turn = 1;
        }
    }
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
