#ifndef PROJDRILL_ITEMSENDER_H
#define PROJDRILL_ITEMSENDER_H
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "QTimer"
#include "ItemGetter.h"
#include "../item/ItemsBase.h"
class ItemSender:public QObject,public QGraphicsRectItem
{
    Q_OBJECT
public:
    ItemSender(int posx, int posy, QGraphicsScene* scene,int msec) : QGraphicsRectItem(posx, posy, 44, 44), scene(scene),msec(msec) {
        this->setZValue(2);//getter在sender上方
        scene->addItem(this);
        timer=new QTimer(this);
        timer->start(msec);
        getter= nullptr;
        item_stored= nullptr;
        is_full=false;
        connect(timer, SIGNAL(timeout()), this, SLOT(move_item()));
    };
    void reconnect();
    bool is_full;
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
