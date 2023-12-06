#include "MachineConveyor.h"

MachineConveyor::MachineConveyor(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(4, QPixmap(QString::fromStdString(img_path(4))), scene, pos, towards) {
	timer_running = false;
	timer = new QTimer(this);
	speed = 5;
	qDebug() << this->pos().x() << " " << this->pos().y();
	getter = new ItemGetter(this->pos().x() - position[towards][0] * 44,
							this->pos().y() - position[towards][1] * 44, towards, scene);
	qDebug() << "getter inited:" << &getter;
	sender = new ItemSender(this->pos().x(), this->pos().y(), towards, scene, 1000);
	qDebug() << "sender inited:" << &sender;
	connect(getter, SIGNAL(item_get(BasicItems * )), this, SLOT(add_item(BasicItems * )));
	connect(this, SIGNAL(remove_item(BasicItems * )), sender, SLOT(get_item(BasicItems * )));
	connect(timer, SIGNAL(timeout()), this, SLOT(move_item()));
}

MachineBase *MachineConveyor::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineConveyor(scene, pos, towards);
}

void MachineConveyor::move_item() {
	if (items.empty()) {
		timer_running = false;
		timer->stop();
	}
	for (BasicItems *item: items) {
		if (item->pixels_moved >= 44) {
			if (sender->is_full) return;
			else {
				emit remove_item(item);
				items.dequeue();
				if (getter->is_full) getter->is_full = false;
			}
		} else {
			item->moveBy(speed * position[towards][0], speed * position[towards][1]);
			item->pixels_moved += speed;
		}
	}
}

void MachineConveyor::add_item(BasicItems *new_item) {
	if (items.size() >= MAX_ITEM_HOLD) {
		getter->is_full = true;
		return;
	}
	if (timer_running == false) {
		timer_running = true;
		timer->start(80);
	}
	items.append(new_item);
	new_item->pixels_moved = 0;
}

string MachineConveyor::detail_info() {
	return MachineBase::detail_info() +"\ntimer_running:" + to_string(timer_running) +"\nspeed:" +
		   to_string(speed)+"\nitem in queue:"+ to_string(items.size());
}
