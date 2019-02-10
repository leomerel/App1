#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include "character.h"
#include "ground.h"

class Enemy: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QString image_path, QPointF pos);
    void setHealth(int health);
    int health() const;
    void remove();

    void setPosition(int x, int y);

public slots:
    void move();

protected:
    int m_health;
    int m_speed;
    QString m_image_path;
    int m_size;
    QVector<QPointF> enemy_path;
    QPointF m_position;
};

#endif // ENEMY_H
