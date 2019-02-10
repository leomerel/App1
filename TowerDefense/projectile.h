#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Projectile
:  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Projectile(QString image_path);
public slots:
   void move();
protected:
   QString m_image_path;
};

#endif // PROJECTILE_H
