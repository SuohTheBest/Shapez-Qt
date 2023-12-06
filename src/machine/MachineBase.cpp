#include "MachineCutter.h"
#include "MachineCenter.h"
#include "MachineRubbishBin.h"
#include "MachineDriller.h"
#include "MachineConveyor.h"

const int MachineBase::machine_size[TYPES_OF_MACHINES][2]={{2,2},{2,1},{1,1},{1,1},{1,1}};
const string MachineBase::machine_info[TYPES_OF_MACHINES]={"交付中心","切割机","垃圾桶","矿井挖掘","传送带"};
MachineBase* (*MachineBase::to_base[TYPES_OF_MACHINES])(QGraphicsScene *scene,QPointF &pos,short towards) ={MachineCenter::to_base,MachineCutter::to_base,MachineRubbishBin::to_base,MachineDriller::to_base,MachineConveyor::to_base};
const int MachineBase::position[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
string MachineBase::img_path()
{
    return "./img/machine/"+to_string(machine_id)+".png";
}

string MachineBase::detail_info()
{
    return machine_info[machine_id]+"\npos:"+ to_string(pos().x())+" "+ to_string(pos().y());
}

string MachineBase::img_path(int type) {
    return "./img/machine/"+to_string(type)+".png";
}

int MachineBase::size_x()
{
    return machine_size[machine_id][0];
}

int MachineBase::size_y()
{
    return machine_size[machine_id][1];
}
