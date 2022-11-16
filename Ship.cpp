#include "Ship.hpp"

Ship::Ship()
{
    m_name = "";
    m_length = 0;
    m_startx = 0;
    m_starty = 0;
    m_endx = 0;
    m_endy = 0;
    m_num_spaces_left = m_length;
}

Ship::Ship(QString name, uint length)
{
    m_name = name;
    m_length = length;
    m_num_spaces_left = length;
    m_startx = 0;
    m_starty = 0;
    m_endx = m_startx+length;
    m_endy = 0;
}

void Ship::setPostion(uint start_x, uint start_y, Direction dir)
{
    m_startx = start_x;
    m_starty = start_y;
    if (dir == Direction::Vertical)
    {
        m_endx = m_startx;
        m_endy = m_starty + m_length;
    }
    else
    {
        m_endy = m_starty;
        m_endx = m_startx + m_length;
    }
}

void Ship::decrementSpacesLeft()
{
    if (m_num_spaces_left > 0)
    {
        m_num_spaces_left -= 1;
    }
}

int Ship::numSpacesLeft() const
{
    return m_num_spaces_left;
}

QString Ship::getName() const
{
    return m_name;
}


