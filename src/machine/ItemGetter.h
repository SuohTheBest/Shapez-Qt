#ifndef PROJDRILL_ITEMGETTER_H
#define PROJDRILL_ITEMGETTER_H

#include "QGraphicsItem"
#include "../item/ItemsBase.h"
#include <QGraphicsScene>
#include "QDebug"
#include "QTimer"
class ItemGetter : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
	ItemGetter(int posx, int posy, short towards, QGraphicsScene *scene);

	void set_full(int msec=250);

	int type() const override {
		return 23;
	}

	bool is_full;
	short towards;
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
