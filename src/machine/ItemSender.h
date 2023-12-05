#ifndef PROJDRILL_ITEMSENDER_H
#define PROJDRILL_ITEMSENDER_H
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "QTimer"
#include "QDebug"
#include "ItemGetter.h"
#include "../item/ItemsBase.h"
/**
 *  @brief 一个不可见的QGraphicsRectItem对象，用于机器产生物品
 *  @brief 机器类需要connect到get_item()槽函数
 * */
class ItemSender:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    ItemSender(int posx, int posy,short towards, QGraphicsScene* scene,int mse=1000);
    void reconnect();
    bool is_full;
	short towards;
    int type() const override
	{
        return 22;
	}
public slots:
    void get_item(BasicItems* Item);
    void connect_with_getter();//itemsender与itemgetter应当重合
signals:
    void item_get(BasicItems* Item);
private:
    QGraphicsScene *scene;
    BasicItems *item_stored;
    QTimer *timer;
    ItemGetter* getter;
    int msec;
};
#endif//PROJDRILL_ITEMSENDER_H
