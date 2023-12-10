#include "ItemSender.h"
#include "QDebug"

ItemSender::ItemSender(int posx, int posy, short towards, QGraphicsScene *scene, int msec) :
		QGraphicsRectItem(0, 0, 44, 44), towards(towards), scene(scene), msec(msec) {
	this->setZValue(2);//getter在sender上方
	this->setBrush(Qt::red);
	this->setOpacity(0.3);
	this->setPos(posx, posy);
	qDebug() << "Sender_pos:" << this->pos() << "towards:" << towards;
	timer = new QTimer(this);
	wait_timer = new QTimer(this);
	getter = nullptr;
	is_full = true;
	connect(timer, SIGNAL(timeout()), this, SLOT(connect_with_getter()));
	connect(wait_timer, SIGNAL(timeout()), this, SLOT(check_is_full()));
	scene->addItem(this);
	timer->start(msec);
};

void ItemSender::connect_with_getter() {
	QList<QGraphicsItem *> itemsInRect = scene->items(QPointF(this->pos().x() + 1, this->pos().y() + 1));
			foreach (QGraphicsItem *item, itemsInRect) {
			ItemGetter *itemgetter = dynamic_cast<ItemGetter *>(item);
			if (itemgetter) {
				if (itemgetter->towards != this->towards || itemgetter->zValue() != 3)continue;
				this->getter = itemgetter;
				qDebug() << this->pos() << "Connected!" << getter->pos();
				timer->stop();
				connect(this, SIGNAL(item_get(BasicItems * )), getter, SLOT(get_item(BasicItems * )));
				is_full = false;
			}
		}
}

void ItemSender::get_item(BasicItems *Item) {
	emit item_get(Item);
	if (getter->is_full) {
		is_full = true;
		wait_timer->start(250);
	} else {
		is_full = false;
	}
}

void ItemSender::reconnect() {
	is_full = true;
	if (getter == nullptr);
	else {
		disconnect(this, SIGNAL(item_get(BasicItems * )), getter, SLOT(get_item(BasicItems * )));
		getter = nullptr;
		timer->start(msec);
	}
}

ItemSender::ItemSender(QPointF pos, short towards, QGraphicsScene *scene) :
		ItemSender(pos.x(), pos.y(), towards, scene) {}

void ItemSender::check_is_full() {
	if (getter == nullptr || getter->is_full)return;
	is_full = false;
	wait_timer->stop();
}

bool ItemSender::check_is_legal(BasicItems *item) {
    if(getter==nullptr)return false;
    return getter->check_is_leagl(item)&& !this->is_full;
};
