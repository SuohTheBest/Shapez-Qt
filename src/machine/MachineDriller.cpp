#include "MachineDriller.h"

MachineDriller::MachineDriller(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(3, QPixmap(QString::fromStdString(img_path(3))), scene, pos, towards) {
    QList<QGraphicsItem*> allItems = scene->items();
    item_id=-1;
    foreach (QGraphicsItem* item, allItems) {
        if (item->zValue() == 0 && item->pos() == pos) {
            MapBlockItem* block=dynamic_cast<MapBlockItem*>(item);
            item_id=block->type;
            break;
        }
    }
    if (item_id==-1)qDebug()<<"Error,could not find item id.";
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
    qDebug() << "drill!"<<new_item->pos() << item_id;
	scene->addItem(new_item);
	emit item_drilled(new_item);
}
