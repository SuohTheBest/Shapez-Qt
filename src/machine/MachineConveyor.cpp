#include "MachineConveyor.h"

MachineConveyor::MachineConveyor(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(4, QPixmap(QString::fromStdString(img_path(4))), scene, pos, towards) {
	timer_running = false;
	timer = new QTimer(this);
	speed = 3;
	turns = 0;
	this->setZValue(1);
	getter = new ItemGetter(this->pos().x() - position[towards][0] * 44,
							this->pos().y() - position[towards][1] * 44, towards, scene);
	sender = new ItemSender(this->pos().x(), this->pos().y(), towards, scene, 1000);
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
		return;
	}
	if (distance(QPointF(mid_pos(items[0])), end_pos()) <= 0) {
		if (!sender->is_full) {
			emit remove_item(items[0]);
			items[0]->moveBy(speed * position[sender->towards][0], speed * position[sender->towards][1]);
			items.dequeue();
			if (getter->is_full) getter->is_full = false;
		}
	}
	for (int i = 0; i < items.size(); i++) {
		BasicItems *item = items[i];
		QPointF mid(pos().x() + 22, pos().y() + 22);
		int distance_to_mid = position[towards][0] * (mid.x() - item->x() - 9) +
							  position[towards][1] * (mid.y() - item->y() - 9);
		if (distance_to_mid <= 0) {
			if (position[sender->towards][0] == 0 && item->pos().x() != mid.x() - 9) {
				item->setPos(mid.x() - 9, item->pos().y());
			} else if (position[sender->towards][1] == 0 && item->pos().y() != mid.y() - 9) {
				item->setPos(item->pos().x(), mid.y() - 9);
			}
		} else {
			if (position[towards][0] == 0 && item->pos().x() != mid.x() - 9) {
				item->setPos(mid.x() - 9, item->pos().y());
			} else if (position[towards][1] == 0 && item->pos().y() != mid.y() - 9) {
				item->setPos(item->pos().x(), mid.y() - 9);
			}
		}
		if ((i > 0 && is_distance_enough(item->pos(), items[i - 1]->pos())) ||
			(i == 0 && distance(mid_pos(item), end_pos()) > 0)) {
			distance_to_mid = position[towards][0] * (mid.x() - item->x() - 9) +
							  position[towards][1] * (mid.y() - item->y() - 9);
			if (distance_to_mid <= 0) {
				item->moveBy(speed * position[sender->towards][0], speed * position[sender->towards][1]);
			} else {
				item->moveBy(speed * position[towards][0], speed * position[towards][1]);
			}
		}
	}
}

void MachineConveyor::add_item(BasicItems *new_item) {
	if (items.size() >= MAX_ITEM_HOLD) {
		getter->is_full = true;
		return;
	}
	if (!timer_running) {
		timer_running = true;
		timer->start(50);
	}
	items.append(new_item);
	if (items.size() >= MAX_ITEM_HOLD) {
		getter->is_full = true;
	}
}

string MachineConveyor::detail_info() {
	return MachineBase::detail_info() + "\ntimer_running:" + to_string(timer_running) + "\nspeed:" +
		   to_string(speed) + "\nitem in queue:" + to_string(items.size()) + "\ntowards:" + to_string(towards) +
		   "\nsender_towards:" + to_string(sender->towards) + "\nend_pos:" + to_string(end_pos().x()) + " " +
		   to_string(end_pos().y()) + "\ngetter.is_full:" + to_string(getter->is_full) + "\nsender.is_full:" +
		   to_string(sender->is_full);
}

void MachineConveyor::rotate() {
	if (turns != 1)sender->towards = (sender->towards + 1) % 4;
	else sender->towards = (sender->towards + 2) % 4;
	turns = (turns + 1) % 3;
	switch (turns) {
		case 0: {
			MachineBase::setPixmap(QPixmap("./img/machine/4.png"));
			break;
		}
		case 1: {
			MachineBase::setPixmap(QPixmap("./img/machine/4-right.png"));
			break;
		}
		case 2: {
			MachineBase::setPixmap(QPixmap("./img/machine/4-left.png"));
			break;
		}
		default:
			break;
	}
	sender->reconnect();
}

QPointF MachineConveyor::end_pos() {
	return QPointF(pos().x() + 22 + 22 * position[sender->towards][0],
				   pos().y() + 22 + 22 * position[sender->towards][1]);
}

bool MachineConveyor::is_distance_enough(QPointF curr, QPointF prev) {
	int distance = MachineConveyor::distance(curr, prev);
	return distance < 8 ? false : true;
}

int MachineConveyor::distance(QPointF curr, QPointF prev) {
	int distance =
			position[towards][0] * (prev.x() - curr.x()) + position[towards][1] * (prev.y() - curr.y());
	if (towards != sender->towards)
		distance += position[sender->towards][0] * (prev.x() - curr.x()) +
					position[sender->towards][1] * (prev.y() - curr.y());
	return distance;
}

QPointF MachineConveyor::mid_pos(BasicItems *item) {
	return QPointF(item->x() + 9.5, item->y() + 9.5);
}
