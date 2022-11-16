#include "GameBoardTest.hpp"
#include "QRandomGenerator"

static constexpr uint MAX_X_SIZE = 10;
static constexpr uint MAX_Y_SIZE = 10;
GameBoardTest::GameBoardTest(QObject *parent): QAbstractListModel(parent)
{
    beginResetModel();
    for (int i = 0; i < MAX_X_SIZE * MAX_Y_SIZE; i++)
    {
        m_data.append(BoardTileTest());
    }
    endResetModel();


    // BattleShip first
    uint xref = 0;
    uint yref = 0;
    int currIdx = 0;
    Direction dir;
    QString shipName = "BattleShip";
    m_ships.append(Ship(shipName, BATTLESHIPLEN));
    // randomly until valid ship configuration
    findPlaceShip(&xref, &yref, &dir, BATTLESHIPLEN);
    placeShip(&xref, &yref, &dir, shipName, BATTLESHIPLEN);
    m_ships[currIdx].setPostion(xref, yref, dir);
    currIdx += 1;
    shipName = "Cruiser";
    for (int i = 0; i < NUMCRUISERS; i ++)
    {
        xref = 0;
        yref = 0;
        m_ships.append(Ship(shipName, CRUISERLEN));
        findPlaceShip(&xref, &yref, &dir, CRUISERLEN);
        placeShip(&xref, &yref, &dir, shipName, CRUISERLEN);
        m_ships[currIdx].setPostion(xref, yref, dir);
        currIdx += 1;
    }
    shipName = "Destroyer";
    for (int i = 0; i < NUMDESTROYERS; i ++)
    {
        xref = 0;
        yref = 0;
        m_ships.append(Ship(shipName, DESTROYERLEN));
        findPlaceShip(&xref, &yref, &dir, DESTROYERLEN);
        placeShip(&xref, &yref, &dir, shipName, DESTROYERLEN);
        m_ships[currIdx].setPostion(xref, yref, dir);
        currIdx += 1;
    }
    shipName = "Sub";
    for (int i = 0; i < NUMSUBMARINES; i ++)
    {
        xref = 0;
        yref = 0;
        m_ships.append(Ship(shipName, SUBMARINELEN));
        findPlaceShip(&xref, &yref, &dir, SUBMARINELEN);
        placeShip(&xref, &yref, &dir, shipName, SUBMARINELEN);
        m_ships[currIdx].setPostion(xref, yref, dir);
        currIdx += 1;
    }
    qDebug() << "built";
}

int GameBoardTest::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid())
		return 0;
	
	return m_data.count();
}

QVariant GameBoardTest::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
     switch (role) {
         case Qt::DisplayRole:
         case NameRole:
         //qDebug() << "string: " << m_data.at(index.row()).getName();
             return QVariant(m_data.at(index.row()).getName());
         case TcolorRole:
             return QVariant(m_data.at(index.row()).getColor());
     }
    return QVariant();
}

QHash<int, QByteArray> GameBoardTest::roleNames() const
{
	static QHash<int, QByteArray> mapping {
        {NameRole, "name"},
        {TcolorRole, "tcolor"}
	};
	return mapping;
}

void GameBoardTest::modifyIndex(int index, BoardTileTest changeTo)
{
    if (index < m_data.size())
    { 
        beginResetModel();
        m_data[index] = changeTo;
        endResetModel();
    }
}

void GameBoardTest::modifyCoord(uint x, uint y, BoardTileTest changeTo)
{
    if ((x > MAX_X_SIZE) || (y > MAX_Y_SIZE))
    {
        return;
    }
    modifyIndex(flatIndexer(x,y),changeTo);
}

void GameBoardTest::findPlaceShip(uint *xref, uint *yref, Direction *dir, int length)
{
    bool valid = true;
    do
    {
        valid = true; // reset
        *dir = (randomFlipper())? Direction::Vertical: Direction::Horizontal;
        quint32 placement = QRandomGenerator::global()->bounded( 100 );
        //get start point
        arrayIndexer((int)placement, xref, yref);
        int tempx = *xref;
        int tempy = *yref;

        if (*dir == Direction::Vertical)
        {
            if (tempy + length > 9)
            {
                valid = false;
            }
            else
            {
                // check other ships, within 1 space distance
                for (int i = 0; i < length; i++)
                {
                    if (m_data.at(flatIndexer(tempx, tempy + i)).getName() != "Water")
                    {
                        valid = false;
                    }
                }
            }
        }
        else
        {
            if (tempx + length > 9)
            {
                valid = false;
            }
            else
            {
                // check other ships
                for (int i = 0; i < length; i++)
                {
                    if (m_data.at(flatIndexer(tempx + i, tempy)).getName() != "Water")
                    {
                        valid = false;
                    }
                }
            }
        }
    } while(!valid);
}

void GameBoardTest::placeShip(uint *xref, uint *yref, Direction *dir, QString name, int length)
{
    uint tempx = *xref;
    uint tempy = *yref;
    Direction tempDir = *dir;
    for (int i = 0; i < length; i++)
    {
        if (tempDir == Direction::Vertical)
        {
            modifyCoord(tempx, tempy + i, BoardTileTest(name, "grey"));
        }
        else
        {
            modifyCoord(tempx + i, tempy, BoardTileTest(name, "grey"));
        }
    }
}

void GameBoardTest::shotAt()
{
    uint xref = 0;
    uint yref = 0;
    bool valid = true;
    do
    {
        valid = true; // reset
        quint32 placement = QRandomGenerator::global()->bounded( 100 );
        //get start point
        arrayIndexer((int)placement, &xref, &yref);
        int tempx = xref;
        int tempy = yref;

        if (tempy > 9)
        {
            valid = false;
        }
        else if (tempx > 9)
        {
            valid = false;
        }
        else
        {
            // check other shots
            if (m_data.at(flatIndexer(tempx, tempy)).getName() == "Shot")
            {
                valid = false;
            }
            else if (m_data.at(flatIndexer(tempx, tempy)).getName() != "Water")
            {
                //hit ship, change color red
                QString key = m_data.at(flatIndexer(tempx, tempy)).getName();
                for (int i = 0; i < m_ships.size(); i++)
                {
                    if ((m_ships.at(i).getName() == key) && (m_ships.at(i).numSpacesLeft() > 0))
                    {
                        m_ships[i].decrementSpacesLeft();
                        break;
                    }
                }
                modifyCoord(tempx, tempy, BoardTileTest("Shot", "red"));
            }
            else
            {
                //hit water, change color black
                modifyCoord(tempx, tempy, BoardTileTest("Shot", "black"));
            }

        }
    } while(!valid);
}

int GameBoardTest::getShipSpaces() const
{
    int shipSpaces = 0;
    for (int i =0; i < m_ships.size(); i++)
    {
        shipSpaces += m_ships[i].numSpacesLeft();
    }
    return shipSpaces;
}

int GameBoardTest::flatIndexer(uint x, uint y)
{
   return x+y*10;
}

void GameBoardTest::arrayIndexer(int index, uint *x, uint *y)
{
    if (index < MAX_X_SIZE * MAX_Y_SIZE)
    {
        if (index < 10)
        {
            *x = index;
            *y = 0;
        }
        else if (index == (MAX_X_SIZE * MAX_Y_SIZE) - 1)
        {
            *x = MAX_X_SIZE - 1;
            *y = MAX_Y_SIZE - 1;
        }
        else
        {
            int rem = index % 10;
            index -= rem;
            int yindex = 0;
            do
            {
                index -= 10;
                yindex += 1;
            } while(index > 1);

            *x = rem;
            *y = yindex;
        }
    }
}

bool GameBoardTest::overlapDetected(uint x, uint y)
{
   return x+y*10;
}

bool GameBoardTest::randomFlipper()
{
    quint32 coinflip = QRandomGenerator::global()->bounded( 8 );
    if (coinflip % 2 == 0)
        return true;
    else
        return false;
}
