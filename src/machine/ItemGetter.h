#ifndef PROJDRILL_ITEMGETTER_H
#define PROJDRILL_ITEMGETTER_H

#include "QGraphicsItem"
#include "../item/ItemsBase.h"
#include <QGraphicsScene>
#include "QDebug"
#include "QTimer"
/**
 * @brief 用于机器接收物品，发出信号item_get
 */
class ItemGetter : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
	ItemGetter(int posx, int posy, short towards, QGraphicsScene *scene, QObject *parent, short permit_item_id = -1);

	~ItemGetter();

	void set_full(int msec = 250);

	bool check_is_leagl(BasicItems *item);

	int type() const override {
		return 23;
	}

	bool is_full;
	short towards;
	short permit_item_id;
public slots:

	void get_item(BasicItems *Item);

	void set_free();

signals:

	void item_get(BasicItems *Item);

private:
	QTimer *timer;
	QGraphicsScene *scene;
};

#endif//PROJDRILL_ITEMGETTER_H
