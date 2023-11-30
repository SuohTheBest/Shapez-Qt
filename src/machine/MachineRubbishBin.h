#ifndef PROJDRILL_MACHINERUBBISHBIN_H
#define PROJDRILL_MACHINERUBBISHBIN_H
#include "MachineBase.h"
class MachineRubbishBin:public MachineBase
{
public:
    MachineRubbishBin(QGraphicsScene *scene);
    static MachineBase* to_base(QGraphicsScene *scene);
private:
};
#endif//PROJDRILL_MACHINERUBBISHBIN_H
