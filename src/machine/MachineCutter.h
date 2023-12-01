#ifndef PROJDRILL_MACHINECUTTER_H
#define PROJDRILL_MACHINECUTTER_H
#include "MachineBase.h"
class MachineCutter:public MachineBase
{
public:
    MachineCutter(QGraphicsScene *scene,QPointF &pos,short towards);
    static MachineBase* to_base(QGraphicsScene *scene,QPointF &pos,short towards);
private:
    int *storage;

};
#endif//PROJDRILL_MACHINECUTTER_H
