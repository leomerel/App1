#include "square.h"

Square::Square(int x, int y, int size)
{
    square = new QGraphicsRectItem(QRectF(x, y, size, size),this);
}
