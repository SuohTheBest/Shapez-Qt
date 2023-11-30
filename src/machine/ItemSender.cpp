#include "ItemSender.h"
#include "QDebug"
ItemSender::ItemSender(int posx, int posy, QGraphicsScene* scene,int msec) : QGraphicsRectItem(0, 0, 44, 44), scene(scene),msec(msec) {
    this->setZValue(2);//getter在sender上方
    this->setBrush(Qt::red);
    this->setOpacity(0.3);
    this->setPos(posx,posy);
    qDebug()<<"Sender_pos:"<<this->pos();
    timer=new QTimer(this);
    getter= nullptr;
    item_stored= nullptr;
    is_full=false;
    connect(timer, SIGNAL(timeout()), this, SLOT(connect_with_getter()));
    scene->addItem(this);
    timer->start(msec);
};

void ItemSender::connect_with_getter() {
    QGraphicsItem* graphicsItem=scene->itemAt(this->pos(),QTransform());
    qDebug()<<this->pos();
    if(graphicsItem->zValue()==3)
    {
        this->getter=static_cast<ItemGetter*>(graphicsItem);//6d138b0 36ed2e0 6c713d0
        qDebug()<<"Connected!";
        timer->stop();
        connect(this, SIGNAL(item_get(BasicItems*)),getter,SLOT(get_item(BasicItems*)));
        if(is_full&&!getter->is_full)
        {
            is_full=false;
            emit item_get(item_stored);
            item_stored= nullptr;
        }
    }
    else
        return ;
}

void ItemSender::get_item(BasicItems* Item)
{
    if(getter== nullptr)
    {
        qDebug()<<"getter is nullptr";
    }
    if(getter== nullptr||getter->is_full)
    {
        is_full=true;
        item_stored=Item;
    }
    else
    {
        emit item_get(Item);
    }
}

void ItemSender::reconnect() {
    timer->start(msec);
}
