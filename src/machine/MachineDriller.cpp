#include "MachineDriller.h"
MachineDriller::MachineDriller(QGraphicsScene *scene): MachineBase(3,QPixmap(QString::fromStdString(img_path(3))),scene)
{
    QGraphicsItem *item=scene->itemAt(this->pos(), QTransform());
    if(item->zValue()==0)
    {
        MapBlockItem* block=(MapBlockItem*)item;
        this->item_id=block->type;
        qDebug()<<item->zValue();
    }
    else
    {
        qDebug()<<item->zValue();
    }
    timer=new QTimer(this);
    sender=new ItemSender(this->pos().x(),this->pos().y(),scene,DRILLER_TIME);
    connect(this, SIGNAL(item_drilled(BasicItems *)),sender, SLOT(get_item(BasicItems *)));
    connect(timer, SIGNAL(timeout()), this, SLOT(drill()));
    timer->start();
}
MachineBase* MachineDriller::to_base(QGraphicsScene *scene) {
    return new MachineDriller(scene);
}
void MachineDriller::drill() {
    emit item_drilled(new BasicItems(item_id));
}
