#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QGraphicsRectItem>
//#include "ground.h"

class Square: public QObject, public QGraphicsRectItem
{
public:
    Square(int x, int y, int size);
private:
    QGraphicsRectItem *square;
};

#endif // SQUARE_H
