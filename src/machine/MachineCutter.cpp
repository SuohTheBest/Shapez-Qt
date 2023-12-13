#include "MachineCutter.h"

MachineCutter::MachineCutter(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(1, QPixmap(QString::fromStdString(img_path(1))), scene, pos, towards) {
	switch (towards) {
		case 0: {
			getter = new ItemGetter(pos.x(), pos.y() + 44, towards, scene, this);
			sender[0] = new ItemSender(pos, towards, scene, this);
			sender[1] = new ItemSender(pos.x() + 44, pos.y(),
									   towards, scene, this);
			break;
		}
		case 1: {
			getter = new ItemGetter(pos.x(), pos.y(), towards, scene, this);
			sender[0] = new ItemSender(pos.x() + 44, pos.y(), towards, scene, this);
			sender[1] = new ItemSender(pos.x() + 44, pos.y() + 44,
									   towards, scene, this);
			break;
		}
		case 2: {
			getter = new ItemGetter(pos.x() + 44, pos.y(), towards, scene, this);
			sender[0] = new ItemSender(pos.x() + 44, pos.y() + 44, towards, scene, this);
			sender[1] = new ItemSender(pos.x(), pos.y() + 44,
									   towards, scene, this);
			break;
		}
		case 3: {
			getter = new ItemGetter(pos.x() + 44, pos.y() + 44, towards, scene, this);
			sender[0] = new ItemSender(pos, towards, scene, this);
			sender[1] = new ItemSender(pos.x(), pos.y() + 44,
									   towards, scene, this);
			break;
		}
		default: {
			break;
		}
	}
	connect(getter, SIGNAL(item_get(BasicItems * )), this, SLOT(cut(BasicItems * )));
	connect(this, SIGNAL(finish_cut_1(BasicItems * )), sender[0], SLOT(get_item(BasicItems * )));
	connect(this, SIGNAL(finish_cut_2(BasicItems * )), sender[1], SLOT(get_item(BasicItems * )));
}

MachineBase *MachineCutter::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineCutter(scene, pos, towards);
}

void MachineCutter::cut(BasicItems *item) {
	BasicItems *item1;
	BasicItems *item2;
	switch (item->item_id) {
		case 0: {
			item1 = new BasicItems(2, scene);
			item2 = new BasicItems(2, scene);
			item1->setPos(sender[0]->pos().x() + 22, sender[0]->pos().y() + 22);
			item2->setPos(sender[1]->pos().x() + 22, sender[1]->pos().y() + 22);
			delete item;
			break;
		}
		default: {
			break;
		}
	}
	emit finish_cut_1(item1);
	emit finish_cut_2(item2);
	getter->set_full(6000.0 / (*multiplier));
}

string MachineCutter::detail_info() {
	return MachineBase::detail_info() + "\nsender0.is_full:" + to_string(sender[0]->is_full) + "\nsender1.is_full:" +
		   to_string(sender[1]->is_full) + "\ncutting_time:" + to_string(6000 / (*multiplier));
}

bool MachineCutter::is_legal(BasicItems *item) {
	if (item->could_cut && sender[0]->check_is_legal(item) && sender[1]->check_is_legal(item)) {
		return true;
	} else
		return false;
}

void MachineCutter::pause() {
	getter->is_full = true;
}

void MachineCutter::restart() {
	getter->is_full = false;
}

void MachineCutter::set_multiplier(float *multiply) {
	this->multiplier = multiply;
}

void MachineCutter::set_disable() {
	delete getter;
	delete sender[0];
	delete sender[1];
}
