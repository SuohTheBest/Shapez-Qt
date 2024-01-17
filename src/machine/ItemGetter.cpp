#include "ItemGetter.h"
#include "MachineBase.h"

ItemGetter::ItemGetter(int posx, int posy, short towards, QGraphicsScene *scene, QObject *parent, short permit_item_id)
		:
		QGraphicsRectItem(0, 0, 44, 44), towards(towards), scene(scene), permit_item_id(permit_item_id) {
	this->setZValue(3);//getter在sender上方
	this->setParent(parent);
        this->setBrush(QColor(0,0,255));
    this->setOpacity(0.3);
	this->setPos(posx, posy);
	qDebug() << "Getter_pos:" << this->pos() << "towards:" << this->towards;
	scene->addItem(this);
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(set_free()));
	is_full = false;
};

ItemGetter::~ItemGetter() noexcept {
	QList<QGraphicsItem *> itemsInRect = scene->items(QPointF(this->pos().x() + 1, this->pos().y() + 1));
			foreach (QGraphicsItem *item, itemsInRect) {
			ItemSender *itemsender = dynamic_cast<ItemSender *>(item);
			if (itemsender) {
				if (itemsender->towards != this->towards || itemsender->zValue() != 2)continue;
				itemsender->reconnect();
			}
		}
}

void ItemGetter::get_item(BasicItems *Item) {
	emit item_get(Item);
}

void ItemGetter::set_full(int msec) {
	this->is_full = true;
	timer->start(msec);
}

void ItemGetter::set_free() {
	this->is_full = false;
	timer->stop();
}

bool ItemGetter::check_is_leagl(BasicItems *item) {
	if (permit_item_id != -1 && item->item_id != permit_item_id)return false;
	MachineBase *parent = dynamic_cast<MachineBase *>(this->parent());
	return parent->is_legal(item);
}

