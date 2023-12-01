#include "MachineCutter.h"

MachineCutter::MachineCutter(QGraphicsScene *scene, QPointF &pos,short towards) :
		MachineBase(1, QPixmap(QString::fromStdString(img_path(1))), scene, pos,towards) {
	this->storage = new int[10];
}

MachineBase *MachineCutter::to_base(QGraphicsScene *scene, QPointF &pos,short towards) {
	return new MachineCutter(scene, pos,towards);
}
