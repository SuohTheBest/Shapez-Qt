#include "MachineDriller.h"

MachineDriller::MachineDriller(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(3, QPixmap(QString::fromStdString(img_path(3))), scene, pos, towards) {
	QGraphicsItem *item = scene->itemAt(this->pos(), QTransform());
	if (item->zValue() == 0) {
		MapBlockItem *block = (MapBlockItem *) item;
		this->item_id = block->type;
		qDebug() << item->zValue();
	} else {
		qDebug() << item->zValue();
	}
	timer = new QTimer(this);
	sender = new ItemSender(this->pos().x(), this->pos().y(), scene, DRILLER_TIME);
	connect(this, SIGNAL(item_drilled(BasicItems * )), sender, SLOT(get_item(BasicItems * )));
	connect(timer, SIGNAL(timeout()), this, SLOT(drill()));
	timer->start(DRILLER_TIME);
}

MachineBase *MachineDriller::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineDriller(scene, pos, towards);
}

void MachineDriller::drill() {
	if (sender->is_full)return;
	BasicItems *new_item = new BasicItems(item_id);
	new_item->setPos(this->pos().x() + 25, this->pos().y() + 13);
	qDebug() << new_item->pos() << item_id;
	scene->addItem(new_item);
	emit item_drilled(new_item);
}
