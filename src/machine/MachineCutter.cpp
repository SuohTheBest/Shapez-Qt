#include "MachineCutter.h"

MachineCutter::MachineCutter(QGraphicsScene *scene, QPointF &pos, short towards) :
		MachineBase(1, QPixmap(QString::fromStdString(img_path(1))), scene, pos, towards) {
	this->speed = 1000;
	switch (towards) {
		case 0: {
			getter = new ItemGetter(pos.x(), pos.y() + 44, towards, scene);
			sender[0] = new ItemSender(pos, towards, scene);
			sender[1] = new ItemSender(pos.x() + 44, pos.y(),
									   towards, scene);
			break;
		}
		case 1: {
			getter = new ItemGetter(pos.x(), pos.y(), towards, scene);
			sender[0] = new ItemSender(pos.x() + 44, pos.y(), towards, scene);
			sender[1] = new ItemSender(pos.x() + 44, pos.y() + 44,
									   towards, scene);
			break;
		}
		case 2: {
			getter = new ItemGetter(pos.x() + 44, pos.y(), towards, scene);
			sender[0] = new ItemSender(pos.x() + 44, pos.y() + 44, towards, scene);
			sender[1] = new ItemSender(pos.x(), pos.y() + 44,
									   towards, scene);
			break;
		}
		case 3: {
			getter = new ItemGetter(pos.x() + 44, pos.y() + 44, towards, scene);
			sender[0] = new ItemSender(pos, towards, scene);
			sender[1] = new ItemSender(pos.x(), pos.y() + 44,
									   towards, scene);
			break;
		}
		default: {
			break;
		}
	}
	connect(getter, SIGNAL(item_get(BasicItems * )), this, SLOT(cut(BasicItems * )));
	connect(this, SIGNAL(finish_cut_1(BasicItems * )), sender[0], SLOT(get_item(BasicItems * )));
	connect(this, SIGNAL(finish_cut_2(BasicItems * )), sender[1], SLOT(get_item(BasicItems * )));
}

MachineBase *MachineCutter::to_base(QGraphicsScene *scene, QPointF &pos, short towards) {
	return new MachineCutter(scene, pos, towards);
}

void MachineCutter::cut(BasicItems *item) {
	if (!item->could_cut)return;//TODO:IS_FULL
	BasicItems *item1;
	BasicItems *item2;
	switch (item->item_id) {
		case 0: {
			item1 = new BasicItems(2);
			item2 = new BasicItems(2);
			item1->setPos(pos().x(),pos().y());
			item2->setPos(pos().x()+44,pos().y());
			MachineBase::scene->addItem(item1);
			MachineBase::scene->addItem(item2);
			break;
		}
		default: {
			break;
		}
	}
	emit finish_cut_1(item1);
	emit finish_cut_2(item2);
}
