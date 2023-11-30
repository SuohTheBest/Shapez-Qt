#ifndef PROJDRILL_MACHINECENTER_H
#define PROJDRILL_MACHINECENTER_H
#include "MachineBase.h"

class MachineCenter:public MachineBase
{
public:
    MachineCenter(QGraphicsScene *scene,QPointF &pos);
    static MachineBase *to_base(QGraphicsScene *scene,QPointF &pos);
private:
    int *storage;

};
#endif//PROJDRILL_MACHINECENTER_H
