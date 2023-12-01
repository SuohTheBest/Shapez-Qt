#include "MachineCenter.h"

MachineCenter::MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(0, QPixmap(QString::fromStdString(img_path(0))), scene, pos, towards) {
	this->storage = new int[10];
}

MachineBase *MachineCenter::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineCenter(scene, pos, towards);
}
