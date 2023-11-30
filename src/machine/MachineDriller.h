#ifndef MACHINEDRILLER_H
#define MACHINEDRILLER_H
#include "MachineBase.h"

class MachineDriller : public QObject, public MachineBase {
    Q_OBJECT
public:
    MachineDriller(QGraphicsScene *scene);
    static MachineBase *to_base(QGraphicsScene *scene);
public slots:

    signals:
};

#endif// MACHINEDRILLER_H
