#include "Player.hpp"

Player::Player(QObject *parent) : QObject(parent)
{

}

QString Player::someVar()
{
    return m_someVar;
}

QString Player::getSomeVar()
{
    return m_someVar;
}


void Player::setSomeVar(const QString &someVar)
{
    if (someVar == m_someVar)
        return;
    m_someVar = someVar;
    emit someVarChanged(m_someVar);
}

