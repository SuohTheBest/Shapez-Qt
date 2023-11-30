#include "ItemSender.h"
void ItemSender::connect_with_getter() {
    QGraphicsItem* graphicsItem=scene->itemAt(this->pos(),QTransform());
    if(graphicsItem->zValue()==3)
    {
        ItemGetter* getter=(ItemGetter*)graphicsItem;
        this->getter=getter;
        timer->stop();
        connect(this, SIGNAL(item_get(BasicItems* Item)),getter, SLOT(get_item()));
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