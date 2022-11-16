#ifndef _SHIP_H
#define _SHIP_H

#include <QString>
#include "Ship.hpp"

enum Direction
{
    Horizontal = 0,
    Vertical
};

class Ship
{


public:
    Ship();
    explicit Ship(QString name, uint length);
    void setPostion(uint start_x, uint start_y, Direction dir);
    void decrementSpacesLeft();
    int numSpacesLeft() const;
    QString getName() const;
private:
    QString m_name;
    uint m_length;
    uint m_startx;
    uint m_starty;
    uint m_endx;
    uint m_endy;
    uint m_num_spaces_left;
};
#endif
