#include "MachineKiln.h"

MachineKiln::MachineKiln(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(ID_MACHINE_KILN, QPixmap(QString::fromStdString(img_path(ID_MACHINE_KILN))), scene, pos,
					towards) {
	switch (towards) {
		case 0: {
			getter[0] = new ItemGetter(pos.x() - 44, pos.y(), 1, scene, this, ID_ITEM_COAL);
			getter[1] = new ItemGetter(pos.x() + 2 * 44, pos.y() + 44, 0, scene, this, ID_ITEM_SAND);
			sender = new ItemSender(pos.x() + 2 * 44, pos.y(), 0, scene, this);
			break;
		}
		case 1: {
			getter[0] = new ItemGetter(pos.x(), pos.y() - 44, 2, scene, this, ID_ITEM_COAL);
			getter[1] = new ItemGetter(pos.x() - 44, pos.y() + 44 * 2, 1, scene, this, ID_ITEM_SAND);
			sender = new ItemSender(pos.x(), pos.y() + 2 * 44, 1, scene, this);
			break;
		}
		case 2: {
			getter[0] = new ItemGetter(pos.x() + 44, pos.y(), 3, scene, this, ID_ITEM_COAL);
			getter[1] = new ItemGetter(pos.x() - 2 * 44, pos.y() - 44, 2, scene, this, ID_ITEM_SAND);
			sender = new ItemSender(pos.x() - 2 * 44, pos.y(), 2, scene, this);
			break;
		}
		case 3: {
			getter[0] = new ItemGetter(pos.x(), pos.y() + 44, 0, scene, this, ID_ITEM_COAL);
			getter[1] = new ItemGetter(pos.x() + 44, pos.y() - 44 * 2, 3, scene, this, ID_ITEM_SAND);
			sender = new ItemSender(pos.x(), pos.y() - 44 * 2, 3, scene, this);
			break;
		}
		default: {
			break;
		}
	}
	coal = nullptr;
	memset(sand,0, sizeof(BasicItems*)*3);
	connect(getter[0], SIGNAL(item_get(BasicItems * )), this, SLOT(pre_burn(BasicItems * )));
	connect(getter[1], SIGNAL(item_get(BasicItems * )), this, SLOT(pre_burn(BasicItems * )));
	connect(this, SIGNAL(finish_burn(BasicItems * )), sender, SLOT(get_item(BasicItems * )));
}

MachineBase *MachineKiln::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineKiln(scene, pos, towards);
}

string MachineKiln::detail_info() {
	return MachineBase::detail_info() + +"\n输入煤炭与沙子生成玻璃" + "\nburn_time:12000" + "\ncoal == nullptr:" +
		   to_string(coal == nullptr) + "\nsand == nullptr:" + to_string(sand[2] == nullptr);
}

bool MachineKiln::is_legal(BasicItems *item) {
	if (((item->item_id == ID_ITEM_SAND && sand[2] == nullptr) || (item->item_id == ID_ITEM_COAL && coal == nullptr)) &&
		sender->check_is_legal(item)) {
		return true;
	} else
		return false;
}

void MachineKiln::pause() {
	getter[0]->is_full = true;
	getter[1]->is_full = true;
}

void MachineKiln::restart() {
	getter[0]->is_full = false;
	getter[1]->is_full = false;
}

void MachineKiln::set_disable() {
	delete getter[0];
	delete getter[1];
	delete sender;
}

void MachineKiln::pre_burn(BasicItems *item) {
	if (item->item_id == ID_ITEM_COAL)coal = item;
	else sand[index++] = item;
	if (coal != nullptr && sand[2] != nullptr)burn();
}

void MachineKiln::burn() {
	BasicItems *item;
	item = new BasicItems(ID_ITEM_GLASS, scene);
	item->setPos(sender->pos().x() + 22, sender->pos().y() + 22);
	delete coal;
	delete sand[0];
	delete sand[1];
	delete sand[2];
	coal = nullptr;
	index=0;
	memset(sand,0,sizeof(BasicItems*)*3);
	emit finish_burn(item);
	getter[0]->set_full(12000);
	getter[1]->set_full(12000);
}
