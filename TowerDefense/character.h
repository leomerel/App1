#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Character(int range = 10, QString image_path = 0);
    virtual int get_health();
    virtual void set_health(int health);
    virtual int get_range();
    virtual void set_range(int range);
    virtual int get_size();
    virtual void set_image_path(QString path);

protected:
    int m_health;
    int m_range;
    QGraphicsPolygonItem * attack_area;
    QString m_image_path;
    int m_size;


};

#endif // CHARACTER_H
