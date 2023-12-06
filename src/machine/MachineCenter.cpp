#include "MachineCenter.h"

MachineCenter::MachineCenter(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(0, QPixmap(QString::fromStdString(img_path(0))), scene, pos, towards) {
	this->gold = 0;
	this->level = 1;
	int size = level + 1;
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * i, pos.y() - 44, 2, scene));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * size, pos.y() + 44 * i, 3, scene));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() + 44 * size - 44 * i - 44, pos.y() + 44 * size, 0, scene));
	}
	for (int i = 0; i < level + 1; ++i) {
		getter.push_back(new ItemGetter(pos.x() - 44, pos.y() + 44 * i, 1, scene));
	}
	for (int i = 0; i < getter.size(); ++i) {
		connect(getter[i], SIGNAL(item_get(BasicItems * )), this, SLOT(get_items(BasicItems * )));
	}
}

void MachineCenter::get_items(BasicItems *item) {
	gold += item->value;
	delete item;
}

MachineBase *MachineCenter::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineCenter(scene, pos, towards);
}

string MachineCenter::detail_info() {
	return MachineBase::detail_info()+"\n"+"gold:"+ to_string(gold);
}
