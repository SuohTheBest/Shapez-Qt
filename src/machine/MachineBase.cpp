#include "MachineCutter.h"
#include "MachineCenter.h"
#include "MachineRubbishBin.h"
#include "MachineDriller.h"
#include "MachineConveyor.h"
#include "MachineBase.h"
#include "MachineBallMill.h"
#include "MachineKiln.h"

const int MachineBase::machine_size[TYPES_OF_MACHINES][2] = {{2, 2},
															 {2, 1},
															 {1, 1},
															 {1, 1},
															 {1, 1},
															 {4, 1},
															 {3, 1}};
const string MachineBase::machine_info[TYPES_OF_MACHINES] = {"交付中心", "切割机", "垃圾桶", "矿井挖掘", "传送带",
															 "球磨", "烧窑"};

MachineBase *
(*MachineBase::to_base[TYPES_OF_MACHINES])(QGraphicsScene *scene, QPointF &pos, short towards) ={MachineCenter::to_base,
																								 MachineCutter::to_base,
																								 MachineRubbishBin::to_base,
																								 MachineDriller::to_base,
																								 MachineConveyor::to_base,
																								 MachineBallMill::to_base,
																								 MachineKiln::to_base};

const int MachineBase::position[4][2] = {{0,  -1},
										 {1,  0},
										 {0,  1},
										 {-1, 0}};

string MachineBase::detail_info() {
	return machine_info[machine_id] + "\npos:" + to_string(pos().x()) + " " + to_string(pos().y());
}

string MachineBase::img_path(int type) {
	return "./img/machine/" + to_string(type) + ".png";
}

int MachineBase::size_x() {
	return machine_size[machine_id][0];
}

int MachineBase::size_y() {
	return machine_size[machine_id][1];
}

bool MachineBase::is_legal(BasicItems *item) {
	return true;
}

void MachineBase::pause() { return; }

void MachineBase::restart() { return; }

void MachineBase::set_disable() { return; }
