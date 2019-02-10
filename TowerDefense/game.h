#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "character.h"
#include "swordsman.h"
#include "archer.h"
#include <QMouseEvent>
#include <QEvent>
#include <QPointF>
#include "ground.h"
#include "enemy.h"


class Game: public QGraphicsView
{
public:
    Game(QWidget * parent=0);
    //Mouse events
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event, Swordsman * swordsman);

    //Characters
    Swordsman * get_swordsman();
    Swordsman * add_swordsman(QPointF pos);
    void move_swordsman(QPointF pos, Swordsman * swordsman);

    //Map
    void new_soil(int size, QPointF position);
    void new_grass(int size, QPointF position);
    void create_map();
    QVector<Ground*> get_map();
    void set_map(Ground *ground);
    void show_squares();
    void hide_squares();
    QVector<QPointF> getSoil_points() const;

    //Enemies
    Enemy * add_enemy(QPointF pos);
    void create_enemy_path();

    int getSoil_size() const;

    QVector<QPointF> getEnemy_path() const;

private:
    QGraphicsScene * scene;
    Swordsman * swordsman;
    Archer * archer;
    QVector<Archer> archers;
    int num_swordsman;
    QVector<Ground*> map;
    int click_type;
    int num_enemies;
    QVector<QPointF> soil_points;
    int soil_size;
    QVector<QPointF> enemy_path;
};


#endif // GAME_H
