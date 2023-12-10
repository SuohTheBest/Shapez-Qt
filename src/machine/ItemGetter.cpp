#include "ItemGetter.h"

ItemGetter::ItemGetter(int posx, int posy, short towards, QGraphicsScene *scene) :
		QGraphicsRectItem(0, 0, 44, 44), towards(towards), scene(scene) {
	this->setZValue(3);//getter在sender上方
	this->setBrush(Qt::blue);
//        QGraphicsPixmapItem *item=new QGraphicsPixmapItem(QPixmap("./img/button/towards.png"));
//        item->setPos(posx,posy);
//        item->setTransformOriginPoint(22,22);
//        item->setRotation(90*towards);
//        item->setZValue(10);
//        scene->addItem(item);
	this->setOpacity(0.3);
	this->setPos(posx, posy);
	qDebug() << "Getter_pos:" << this->pos() << "towards:" << this->towards;
	scene->addItem(this);
	timer=new QTimer(this);
	connect(timer, SIGNAL(timeout()),this, SLOT(set_free()));
	is_full = false;
};

void ItemGetter::get_item(BasicItems *Item) {
	emit item_get(Item);
}

void ItemGetter::set_full(int msec) {
	this->is_full= true;
	timer->start(msec);
}

void ItemGetter::set_free() {
	this->is_full= false;
	timer->stop();
}
