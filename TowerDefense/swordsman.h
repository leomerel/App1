#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "character.h"
#include <QString>

class Swordsman : public Character
{
public:
    Swordsman();
    //void set_pixmap(QString path);
private:
    int m_damage;
    //QString m_path = ":/images/watermelon.png";
};

#endif // SWORDSMAN_H
