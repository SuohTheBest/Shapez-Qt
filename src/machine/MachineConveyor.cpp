#include "MachineConveyor.h"

::int8_t MachineConveyor::position_array[4][2] = {{1,  0},
												  {0,  -1},
												  {-1, 0},
												  {0,  1}};

MachineConveyor::MachineConveyor(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(4, QPixmap(QString::fromStdString(img_path(4))), scene, pos,towards) {
	timer_running = false;
	timer = new QTimer(this);
	speed = 5;
	qDebug() << this->pos().x() << " " << this->pos().y();
	getter = new ItemGetter(this->pos().x() - position_array[towards][0] * 44,
							this->pos().y() - position_array[towards][1] * 44, scene);
	sender = new ItemSender(this->pos().x(), this->pos().y(), scene, 1000);
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
				items.removeOne(item);
				if (getter->is_full) getter->is_full = false;
			}
		}
		item->moveBy(speed * position_array[towards][0], speed * position_array[towards][1]);
		item->pixels_moved += speed;
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
