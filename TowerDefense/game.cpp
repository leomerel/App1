#include "game.h"
#include <QDebug>
#include <QMouseEvent>
#include "projectile.h"
#include <QVector>
#include <QLineF>
#include <QGraphicsLineItem>

Game::Game(QWidget *parent)
    :click_type(0)
    ,num_enemies(0)
    ,num_swordsman(0)
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1720,1080);
    setScene(scene);
    setFixedSize(1720,1080);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    create_map();

    //Characters "creator"
    swordsman = new Swordsman();
    swordsman->setPos(1600,50);
    scene->addItem(swordsman);

    archer = new Archer();
    archer->setPos(1600,150);
    scene->addItem(archer);

    qDebug() << "Health : " << swordsman->get_health();
    qDebug() << "Health : " << archer->get_health();    

    /*QPen pen;
    pen.setWidth(15);
    pen.setColor(Qt::darkGray);
    QLineF line(QPointF(0,0), QPointF(800,800));
    scene->addLine(line,pen);*/

    create_enemy_path();
}

void Game::mousePressEvent(QMouseEvent *event)
{
    //create a projectile
    QPointF pos = event->pos();
    Projectile * arrow = new Projectile(":/images/arrow.png");
    arrow->setPos(pos);
    scene->addItem(arrow);

    /*
     * Press the left mouse button on a character to select it
     * and click again somewhere on the map to add a new character
     * there.
     * To deactivate the selection, press the right mouse button.
     */
    if (event->button() == Qt::LeftButton)
    {
        if(click_type == 0)
        {
            if(pos.x() >= swordsman->x()
                    && pos.x() <= (swordsman->x()+swordsman->get_size())
                    && pos.y()>= (swordsman->y())
                    && pos.y()<= (swordsman->y()+swordsman->get_size()))
            {
                click_type=1;
                swordsman->set_image_path(":/images/cut_watermelon.png");
                show_squares();
            }
        }
        else if(click_type == 1)
        {
            for(auto &elem: map)
            {
                if(elem->contains_pos(pos) && elem->get_type() == 1 && elem->getAvailable())
                {
                    //qDebug() << "Click : " << pos;
                    //qDebug() << "Square : " << elem->pos();
                    add_swordsman(QPointF(elem->x()+elem->get_size()/2,elem->y()+elem->get_size()/2));
                    //qDebug() << "Nombre de swordsman : " << num_swordsman;
                    elem->setAvailable(false);
                    return;
                }
            }

        }

    }
    else if (event->button() == Qt::RightButton)
    {
        click_type = 0;
        swordsman->set_image_path(":/images/watermelon.png");
        hide_squares();

        QVector<QPointF> temporary_soil_points = getSoil_points();
        Enemy * enemy = add_enemy(QPointF(temporary_soil_points[0].x()+100+soil_size/2,temporary_soil_points[0].y()+soil_size/2));
        //scene->addItem(enemy);
        qDebug() << "Nombre d'ennemies : " << num_enemies;
    }
}

void Game::mouseMoveEvent(QMouseEvent *event, Swordsman * swordsman)
{
    move_swordsman(event->pos(), swordsman);
}

Swordsman *Game::get_swordsman()
{
    return swordsman;
}

Swordsman * Game::add_swordsman(QPointF pos)
{
    Swordsman * swordsman = new Swordsman();
    swordsman->setPos(pos.x()-swordsman->get_size()/2,pos.y()-swordsman->get_size()/2);
    num_swordsman++;
    scene->addItem(swordsman);
    return swordsman;
}

void Game::move_swordsman(QPointF pos,Swordsman * swordsman)
{
    swordsman->setPos(pos);
}

void Game::new_soil(int size, QPointF position)
{
    Ground *ground = new Ground(":/images/cobblestone3.jpg", size, 0);
    ground->setPos(position);
    set_map(ground);
    scene->addItem(ground);
}

void Game::new_grass(int size, QPointF position)
{
    Ground *ground = new Ground(":/images/grass.jpg", size, 1);
    ground->setPos(position);
    set_map(ground);
    scene->addItem(ground);
}

void Game::create_map()
{
    soil_size= (scene->height()-100) / 9;

    soil_points << QPointF(0,0) << QPointF(0,1) << QPointF(0,2)
                << QPointF(1,2)
                << QPointF(2,2) << QPointF(2,3) << QPointF(2,4)
                << QPointF(1,4)
                << QPointF(0,4) << QPointF(0,5) << QPointF(0,6) << QPointF(0,7) << QPointF(0,8)
                << QPointF(1,8) << QPointF(2,8) << QPointF(3,8) << QPointF(4,8) << QPointF(5,8) << QPointF(6,8) << QPointF(7,8)
                << QPointF(8,8) << QPointF(8,7) << QPointF(8,6) << QPointF(8,5) << QPointF(8,4)
                << QPointF(7,4)
                << QPointF(6,4) << QPointF(6,5) << QPointF(6,6)
                << QPointF(5,6)
                << QPointF(4,6) << QPointF(4,5) << QPointF(4,4) << QPointF(4,3) << QPointF(4,2) << QPointF(4,1) << QPointF(4,0)
                << QPointF(5,0)
                << QPointF(6,0) << QPointF(6,1) << QPointF(6,2)
                << QPointF(7,2) << QPointF(8,2);

    QVector<QPointF> map_points;
    for(int i=0 ; i<9 ; i++)
    {
        for(int j=0 ; j<9 ; j++)
        {
            map_points << QPointF(i,j);
        }
    }

    for(auto &elem: map_points)
    {

        if(soil_points.contains(elem))
        {
            QPointF point = elem * soil_size;
            point.setX(point.x()+100);
            new_soil(soil_size, point);
        }
        else
        {
            new_grass(soil_size/2,QPointF(elem.x()*soil_size+100,elem.y()*soil_size));
            new_grass(soil_size/2,QPointF(elem.x()*soil_size+100+soil_size/2,elem.y()*soil_size));
            new_grass(soil_size/2,QPointF(elem.x()*soil_size+100,elem.y()*soil_size+soil_size/2));
            new_grass(soil_size/2,QPointF(elem.x()*soil_size+100+soil_size/2,elem.y()*soil_size+soil_size/2));

        }
    }

}

QVector<Ground *> Game::get_map()
{
    return map;
}

void Game::set_map(Ground *ground)
{
    map.append(ground);
}

void Game::show_squares()
{
    for(auto &elem: map)
    {
        elem->show_square();
    }
}

void Game::hide_squares()
{
    for(auto &elem: map)
    {
        elem->hide_square();
    }
}

QVector<QPointF> Game::getSoil_points() const
{
    return soil_points;
}

Enemy *Game::add_enemy(QPointF pos)
{
    Enemy * enemy = new Enemy(":/images/watermelon.png", pos);
    //enemy->setPos(pos);
    num_enemies++;
    scene->addItem(enemy);
    return enemy;

}

void Game::create_enemy_path()
{
    //QVector<QPointF> enemy_path_points;

    QVector<QPointF> temporary_soil_points = getSoil_points();
    for(auto &elem: temporary_soil_points)
    {
        elem*=soil_size;
    }
    qDebug() << "temporary_soil_points : " << temporary_soil_points << endl;
    QPointF prev_pos(temporary_soil_points[0].x()+100+soil_size/2,temporary_soil_points[0].y()+soil_size/2);

    //enemy_path << prev_pos;

    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::red);

    while(!temporary_soil_points.empty())
    {
        //auto &elem = temporary_soil_points[0];
        //if(((prev_pos.x()+1)>=elem.x() && (prev_pos.x()-1)<=elem.x() && (prev_pos.y()+1+soil_size)>=elem.y() && (prev_pos.y()-1+soil_size)<=elem.y())
        //        || ((prev_pos.y()+1)>=elem.y() && (prev_pos.y()-1)<=elem.y() && (prev_pos.x()+1+soil_size)>=elem.x() && (prev_pos.x()-1+soil_size)<=elem.x()))
            QPointF pos(temporary_soil_points[0].x()+100+soil_size/2,temporary_soil_points[0].y()+soil_size/2);
            enemy_path << pos;

            QLineF line(prev_pos, pos);
            temporary_soil_points.remove(0);
            scene->addLine(line,pen);
            //qDebug() << prev_pos << pos;
            //qDebug() << "temporary_soil_points : " << temporary_soil_points << endl;
            prev_pos=pos;
    }
    //qDebug() << enemy_path;
   //qDebug() << elem->pos();
}

int Game::getSoil_size() const
{
    return soil_size;
}

QVector<QPointF> Game::getEnemy_path() const
{
    return enemy_path;
}




