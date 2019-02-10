#include "ground.h"
#include <QRectF>
#include <QPointF>
#include "square.h"

Ground::Ground(QString image_path, int size, int type)
    :m_image_path(image_path)
    ,m_size(size)
    ,m_type(type)
    ,m_available(0)
{
    //set size and image
    QPixmap image(m_image_path);
    setPixmap(image.scaled(m_size,m_size,Qt::IgnoreAspectRatio));

    if(type == 1)
    {
        square = new QGraphicsRectItem(QRectF(0, 0, size, size),this);
        square->hide();
        m_available=1;

        /*for(int i=0 ; i<2 ; i++)
        {
            for(int j=0 ; j<2 ; j++)
            {
                //positions (0,0),(0,1),(1,0),(1,1) and resize it
                int square_size = m_size/2;
                int abs = (i%2)*square_size;
                int ord = (j%2)*square_size;
                QGraphicsRectItem *square = new QGraphicsRectItem(QRectF(x()+abs, y()+ord, 50, 50),this);
                //Square *square = new Square(x()+abs, y()+ord, 50);
                squares.append(square);
            }
        }*/
    }
}

int Ground::get_type()
{
    return m_type;
}

int Ground::get_size()
{
    return m_size;
}

bool Ground::contains_pos(QPointF pos)
{
    if(pos.x() >= x() && pos.x()<x()+m_size
            && pos.y() >= y() && pos.y()<y()+m_size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Ground::show_square()
{
    if(m_type == 1)
    {
        square->show();
    }
}

void Ground::hide_square()
{
    if(m_type == 1)
    {
        square->hide();
    }
}

bool Ground::getAvailable() const
{
    return m_available;
}

void Ground::setAvailable(bool available)
{
    m_available = available;
}




