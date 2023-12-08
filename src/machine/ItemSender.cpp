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
	getter = nullptr;
    is_full = true;
	connect(timer, SIGNAL(timeout()), this, SLOT(connect_with_getter()));
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
                is_full=false;
			}
		}
}

void ItemSender::get_item(BasicItems *Item) {
	if (getter == nullptr || getter->is_full) {
		is_full = true;
	} else {
		emit item_get(Item);
	}
}

void ItemSender::reconnect() {
    is_full=true;
	if (getter == nullptr);
	else {
		disconnect(this, SIGNAL(item_get(BasicItems * )), getter, SLOT(get_item(BasicItems * )));
		getter = nullptr;
		timer->start(msec);
	}
}

ItemSender::ItemSender(QPointF pos, short towards, QGraphicsScene *scene) :
		ItemSender(pos.x(), pos.y(), towards, scene) {};
