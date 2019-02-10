#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPointF>


class Ground: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ground(QString image_path, int size, int type);
    int get_type();
    int get_size();
    bool contains_pos(QPointF pos);
    void show_square();
    void hide_square();

    bool getAvailable() const;
    void setAvailable(bool available);

private:
    int m_type; // 0:soil , 1:grass
    int m_size;
    QString m_image_path;
    //QVector<QGraphicsRectItem*> squares;
    //QVector<Square*> squares;
    bool m_available; // to know if something can be added on it
    QGraphicsRectItem *square;
};

#endif // GROUND_H
