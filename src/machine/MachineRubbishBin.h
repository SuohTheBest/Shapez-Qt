#ifndef PROJDRILL_MACHINERUBBISHBIN_H
#define PROJDRILL_MACHINERUBBISHBIN_H
#include "MachineBase.h"
class MachineRubbishBin:public MachineBase
{
public:
    MachineRubbishBin(QGraphicsScene *scene,QPointF &pos);
    static MachineBase* to_base(QGraphicsScene *scene,QPointF &pos);
private:
};
#endif//PROJDRILL_MACHINERUBBISHBIN_H