#include "projectile.h"
#include <QTimer>
#include <QtMath>

Projectile::Projectile(QString image_path)
    :m_image_path(image_path)
{
    //set image
    QPixmap image(m_image_path);
    setPixmap(image);

    //connect a timer to move()
    QTimer * move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));
    move_timer->start(10);
}

void Projectile::move()
{
    int STEP_SIZE = 10;
    double theta = -90; // degrees

    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);
}
