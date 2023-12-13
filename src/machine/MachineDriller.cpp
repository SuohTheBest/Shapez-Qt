#include "MachineDriller.h"

MachineDriller::MachineDriller(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(3, QPixmap(QString::fromStdString(img_path(3))), scene, pos, towards) {
	QList<QGraphicsItem *> allItems = scene->items();
	item_id = -1;
			foreach (QGraphicsItem *item, allItems) {
			if (item->zValue() == 0 && item->pos() == pos) {
				MapBlockItem *block = dynamic_cast<MapBlockItem *>(item);
				item_id = block->item_type;
				break;
			}
		}
	timer = new QTimer(this);
	sender = new ItemSender(this->pos().x(), this->pos().y(), towards, scene,this);
	qDebug() << "sender inited:" << &sender;
	connect(this, SIGNAL(item_drilled(BasicItems * )), sender, SLOT(get_item(BasicItems * )));
	connect(timer, SIGNAL(timeout()), this, SLOT(drill()));
}

MachineBase *MachineDriller::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineDriller(scene, pos, towards);
}

void MachineDriller::drill() {
	if (sender->is_full)return;
	BasicItems *new_item = new BasicItems(item_id, MachineBase::scene);
	switch (towards) {
		case 0: {
			new_item->setPos(pos().x() + 13, pos().y() + 13);
			break;
		}
		case 1: {
			new_item->setPos(pos().x() + 13, pos().y() + 25);
			break;
		}
		case 2: {
			new_item->setPos(pos().x() + 25, pos().y() + 13);
			break;
		}
		case 3: {
			new_item->setPos(pos().x() + 13, pos().y());
			break;
		}
		default:
			break;
	}
	qDebug() << "drill!" << new_item->pos() << item_id;
	emit item_drilled(new_item);
}

string MachineDriller::detail_info() {
	return MachineBase::detail_info() + "\nitem_id:" + to_string(item_id) + "\nis_full:" + to_string(sender->is_full) +
		   "\ndriller_time:" +
		   to_string(5000.0 / (*multiplier));
}

void MachineDriller::pause() {
	timer->stop();
}

void MachineDriller::restart() {
	timer->start(5000.0 / (*multiplier));
}

void MachineDriller::set_multiplier(float *multiply) {
	this->multiplier = multiply;
	timer->start(5000.0 / (*multiplier));
}

void MachineDriller::set_disable() {
	delete sender;
}
