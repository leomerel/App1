#include "enemy.h"
#include <QList>
#include <QDebug>
#include <QTimer>
#include "game.h"
#include "mathematiques.h"

extern Game * game;

Enemy::Enemy(QString image_path, QPointF pos)
    :m_image_path(image_path)
    ,m_size(40)
    ,m_health(50)
    ,m_position(pos)
{
    QPixmap image(m_image_path);
    setPixmap(image.scaled(m_size,m_size,Qt::IgnoreAspectRatio));

    setPos(pos.x()-m_size/2,pos.y()-m_size/2);

    enemy_path = game->getEnemy_path();

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(10);
}

void Enemy::setHealth(int health)
{
    m_health = health;
}

int Enemy::health() const
{
    return m_health;
}

void Enemy::remove()
{
    //scene()->removeItem(this);
    //delete(this);
    delete this;
}

void Enemy::move()
{
    //QVector<QPointF> soil_points = game->getEnemy_path();
    /*for(auto &elem: soil_points)
    {
        elem*=game->getSoil_size();
        elem.setX(elem.x()+100);
    }*/
    int x1=0,y1=0;

    QPointF direction = enemy_path[0];
    if(isInRange(m_position,direction,10))
    {
        //qDebug() << " YOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO ";
        enemy_path.remove(0);
        //qDebug() << "path " << enemy_path;
        if(enemy_path.empty())
        {
            remove();
        }
    }
    else
    {
        if(m_position.x()<direction.x())
        {
            x1=1;
        }
        if(m_position.x()>direction.x())
        {
            x1=-1;
        }
        if(m_position.y()<direction.y())
        {
            y1=1;
        }
        if(m_position.y()>direction.y())
        {
            y1=-1;
        }
        setPos(x()+2*x1,y()+2*y1);
        setPosition(m_position.x()+2*x1,m_position.y()+2*y1);
    }
    /*if(m_position.x()<direction.x())
    {
        x1=1;
        y1=0;
        setPos(x()+2,y());
        setPosition(m_position.x()+2,m_position.y());
    }
    else if(m_position.x()>direction.x())
    {
        setPos(x()-2,y());
        setPosition(m_position.x()-2,m_position.y());
    }
    else if(m_position.y()<direction.y())
    {
        setPos(x(),y()+2);
        setPosition(m_position.x(),m_position.y()+2);
    }
    else if(m_position.y()>direction.y())
    {
        setPos(x(),y()-2);
        setPosition(m_position.x(),m_position.y()-2);
    }
*/

    /*qDebug() << "Image position: " << pos();
    qDebug() << "Enemy position: " << m_position;
    qDebug() << "Direction: " << direction;*/

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(auto &elem: colliding_items)
    {
        if(typeid(*elem) == typeid (QGraphicsPolygonItem))
        {
            m_health--;
            if(m_health <= 0)
            {
                remove();
            }
        }
    }
    //setPos(x()+2,y()+2);
    //qDebug() << "Enemy health: " << m_health;
}

void Enemy::setPosition(int x, int y)
{
    QPointF position(x,y);
    m_position = position;
}
