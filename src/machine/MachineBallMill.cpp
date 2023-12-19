#include "MachineBallMill.h"

MachineBallMill::MachineBallMill(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(ID_MACHINE_BALLMILL, QPixmap(QString::fromStdString(img_path(ID_MACHINE_BALLMILL))), scene, pos, towards) {
	switch (towards) {
		case 0: {
			getter = new ItemGetter(pos.x() + 44 * 4, pos.y(), 3, scene, this);
			sender = new ItemSender(pos, 3, scene, this);
			break;
		}
		case 1: {
			getter = new ItemGetter(pos.x(), pos.y() + 44 * 4, 0, scene, this);
			sender = new ItemSender(pos, 0, scene, this);
			break;
		}
		case 2: {
			getter = new ItemGetter(pos.x() - 44 * 4, pos.y(), 1, scene, this);
			sender = new ItemSender(pos, 1, scene, this);
			break;
		}
		case 3: {
			getter = new ItemGetter(pos.x(), pos.y() - 44 * 4, 2, scene, this);
			sender = new ItemSender(pos, 2, scene, this);
			break;
		}
		default: {
			break;
		}
	}
	connect(getter, SIGNAL(item_get(BasicItems * )), this, SLOT(mill(BasicItems * )));
	connect(this, SIGNAL(finish_mill(BasicItems * )), sender, SLOT(get_item(BasicItems * )));
}

MachineBase *MachineBallMill::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineBallMill(scene, pos, towards);
}

string MachineBallMill::detail_info() {
	return MachineBase::detail_info()+"\ntime:8000"+"\nsender.is_full:" + to_string(sender->is_full);
}

bool MachineBallMill::is_legal(BasicItems *item) {
	if (item->item_id == ID_ITEM_CAIRN&& sender->check_is_legal(item))return true;
	else return false;
}

void MachineBallMill::pause() {
	getter->is_full = true;
}

void MachineBallMill::restart() {
	getter->is_full = false;
}

void MachineBallMill::set_disable() {
	delete getter;
	delete sender;
}

void MachineBallMill::mill(BasicItems *item) {
	BasicItems *item_out1;
	BasicItems *item_out2;
	switch (item->item_id) {
		case ID_ITEM_CAIRN: {
			item_out1 = new BasicItems(ID_ITEM_SAND, scene);
			item_out1->setPos(sender->pos().x() + 22, sender->pos().y() + 22);
			item_out2 = new BasicItems(ID_ITEM_SAND, scene);
			item_out2->setPos(sender->pos().x() + 22, sender->pos().y() + 22);
			delete item;
			break;
		}
		default: {
			break;
		}
	}
	emit finish_mill(item_out1);
	emit finish_mill(item_out2);
	getter->set_full(8000.0);
}
