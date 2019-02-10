#include "character.h"
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QtMath>
#include <QDebug>

Character::Character(int range, QString image_path)
    : m_range(range)
    , m_image_path(image_path)
{
    //Set the character's image
    m_size = 50;
    QPixmap image(m_image_path);
    setPixmap(image.scaled(m_size,m_size,Qt::IgnoreAspectRatio));

    /*create points vector (to create a polygone
    to represent the range of the character)*/
    QVector<QPointF> points;

    //create 1/4 of the polygon (points have to be in the right order)
    points << QPointF(qCos(M_PI/12),qSin(M_PI/12)) << QPointF(qCos(M_PI/6),qSin(M_PI/6))
           << QPointF(qCos(M_PI/4),qSin(M_PI/4)) << QPointF(qCos(M_PI/3),qSin(M_PI/3))
           << QPointF(qSin(M_PI/12),qCos(M_PI/12)) << QPointF(0,1) ;

    //Duplicate it so it looks like a circle
    QVector<QPointF> points2;
    QVector<QPointF> points3;
    QVector<QPointF> points4;
    for(auto &elem: points)
    {
        elem*=m_range; //increase polygon radius
        QPointF point;
        point.setX(-elem.y());
        point.setY(elem.x());
        points2 << point;
        point.setX(-elem.x());
        point.setY(-elem.y());
        points3 << point;
        point.setX(elem.y());
        point.setY(-elem.x());
        points4 << point;
    }
    points = points + points2 + points3 + points4;

    attack_area = new QGraphicsPolygonItem(QPolygonF(points),this);

    //move the polygon so it fits around the character (so they have the same center)
    QPointF poly_center(0,0);
    poly_center = mapToScene(poly_center);
    QPointF char_center(x()+pixmap().width()/2,y()+pixmap().height()/2);
    QLineF line(poly_center,char_center);
    attack_area->setPos(x()+line.dx(),y()+line.dy());


    //qDebug() << "width : " <<pixmap().width();
}

int Character::get_health()
{
    return m_health;
}

void Character::set_health(int health)
{
    m_health=health;
}

int Character::get_range()
{
    return m_range;
}

void Character::set_range(int range)
{
    m_range=range;
}

int Character::get_size()
{
    return m_size;
}

void Character::set_image_path(QString path)
{
    m_image_path = path;
    QPixmap image(m_image_path);
    setPixmap(image.scaled(m_size,m_size,Qt::IgnoreAspectRatio));
}
