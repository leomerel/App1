#ifndef ARCHER_H
#define ARCHER_H

#include "character.h"

class Archer : public Character
{
public:
    Archer();
private:
    int m_damage;
};

#endif // ARCHER_H
