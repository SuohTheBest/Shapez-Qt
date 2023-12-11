#include "ConstructionButton.h"
#include "QString"

ConstructionButton::ConstructionButton(QGraphicsScene *scene, QWidget *parent) :
		QToolButton(parent), scene(scene) {
	this->machine_id = -1;
	this->setToolButtonStyle(Qt::ToolButtonIconOnly);
	this->setToolTip("建造");
	this->setIconSize(QSize(136, 136));
	this->setIcon(QIcon("./img/button/construction.png"));
	this->setPopupMode(QToolButton::InstantPopup);
	menu = new QMenu();
	signalMapper = new QSignalMapper();
	QAction *actions[TYPES_OF_MACHINES];
	for (int i = 1; i < TYPES_OF_MACHINES; i++) {
		actions[i] = new QAction(QString::fromStdString(MachineBase::machine_info[i]));
		menu->addAction(actions[i]);
		signalMapper->setMapping(actions[i], i);//machine_id
		connect(actions[i], SIGNAL(triggered()), signalMapper, SLOT(map()));
	}
	connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(placeItem(const int &)));
	this->setMenu(menu);
}

void ConstructionButton::placeItem(const int &n) {
	machine_id = n;
}

bool ConstructionButton::is_overlap(QList<MachineBase *> &data, MachineBase *new_item) {
	bool overlap = false;
	for (QGraphicsItem *item: data) {
		if (item->collidesWithItem(new_item)) {
			overlap = true;
			break;
		}
	}
	return overlap;
}

bool ConstructionButton::is_overlap(short (&map)[64][64], MachineBase *new_item) {
	bool overlap = false;
	int pos_x = new_item->x() / 44;
	int pos_y = new_item->y() / 44;
	int size_x = new_item->size_x();
	int size_y = new_item->size_y();
	if (new_item->machine_id == 1 && new_item->towards != 0) {
		switch (new_item->towards) {
			case 1: {
				pos_x += 1;
				swap(size_x, size_y);
				break;
			}
			case 2: {
				pos_y += 1;
				break;
			}
			case 3: {
				swap(size_x, size_y);
				break;
			}
		}
	}
	for (int i = pos_x; i < pos_x + size_x; i++) {
		for (int j = pos_y; j < pos_y + size_y; j++) {
			if (map[i][j] != -1) {
				overlap = true;
				break;
			}
		}
	}
	return overlap;
}

void ConstructionButton::add_item_to_map(short (&map)[64][64], MachineBase *new_item) {
	int pos_x = new_item->x() / 44;
	int pos_y = new_item->y() / 44;
	int size_x = new_item->size_x();
	int size_y = new_item->size_y();
	if (new_item->machine_id == 1 && new_item->towards != 0) {
		switch (new_item->towards) {
			case 1: {
				pos_x += 1;
				swap(size_x, size_y);
				break;
			}
			case 2: {
				pos_y += 1;
				break;
			}
			case 3: {
				swap(size_x, size_y);
				break;
			}
		}
	}
	for (int i = pos_x; i < pos_x + size_x; i++) {
		for (int j = pos_y; j < pos_y + size_y; j++) {
			map[i][j] = new_item->machine_id;
		}
	}
}
