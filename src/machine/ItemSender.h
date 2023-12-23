#ifndef PROJDRILL_ITEMSENDER_H
#define PROJDRILL_ITEMSENDER_H

#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "QTimer"
#include "QDebug"
#include "ItemGetter.h"
#include "../item/ItemsBase.h"

/**
 *  @brief 用于机器产生物品，需要connect到get_item()槽函数
 **/
class ItemSender : public QObject, public QGraphicsRectItem {
Q_OBJECT
public:
	ItemSender(int posx, int posy, short towards, QGraphicsScene *scene,QObject *parent, int msec = 1000);

	ItemSender(QPointF pos, short towards, QGraphicsScene *scene,QObject *parent);

	void reconnect();

	bool is_full;
	short towards;

	int type() const override {
		return 22;
	}

public slots:

	void get_item(BasicItems *Item);

	void check_is_full();

	bool check_is_legal(BasicItems* item);

	void connect_with_getter();//itemsender与itemgetter应当重合
signals:

	void item_get(BasicItems *Item);

private:
	QGraphicsScene *scene;
	QTimer *timer;
	QTimer *wait_timer;
	ItemGetter *getter;
	int msec;
};

#endif//PROJDRILL_ITEMSENDER_H
