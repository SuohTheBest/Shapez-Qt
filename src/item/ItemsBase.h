#ifndef ITEMSBASE_H
#define ITEMSBASE_H

#include "QGraphicsItem"
#include "QPixmap"
#include "QString"
#include "string"
#include "QGraphicsScene"
#include "../BaseDefinitions.h"
using namespace std;
/**
 * @brief 在传送带上移动的物品
 */
class BasicItems : public QGraphicsPixmapItem {
	const static short item_value[TYPES_OF_ITEMS];
public:
	BasicItems(int item_id) :
			QGraphicsPixmapItem(QPixmap(QString::fromStdString("./img/item/" + to_string(item_id) + ".png")), nullptr)
			, item_id(item_id), value(item_value[item_id]), pixels_moved(0) {
		this->setZValue(5);
	};
	~BasicItems()
	{
		scene()->removeItem(this);
	}
	int type() const override {
		return 25;
	}
	short item_id;
	short value;
	short pixels_moved;
};

#endif
