#include "mathematiques.h"

bool isInRange(QPointF p1, QPointF p2, int range)
{
    if(((p1.x() - p2.x()) <= range && (p1.x() - p2.x()) >=0 && (p1.y() - p2.y()) <= range && (p1.y() - p2.y()) >=0)
        || ((p1.x() - p2.x()) <= range && (p1.x() - p2.x()) >=0 && (p1.y() - p2.y()) >= -range && (p1.y() - p2.y()) <=0)
        || ((p1.x() - p2.x()) >= -range && (p1.x() - p2.x()) <=0 && (p1.y() - p2.y()) <= range && (p1.y() - p2.y()) >=0)
        || ((p1.x() - p2.x()) >= -range && (p1.x() - p2.x()) <=0 && (p1.y() - p2.y()) >= -range && (p1.y() - p2.y()) <=0))
    {
        return true;
    }
    else{return false;}
}
