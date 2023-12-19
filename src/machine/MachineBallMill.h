#ifndef PROJDRILL_MACHINEBALLMILL_H
#define PROJDRILL_MACHINEBALLMILL_H
#include "MachineBase.h"

class MachineBallMill : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineBallMill(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	bool is_legal(BasicItems *item) override;

	void pause() override;

	void restart() override;

	void set_disable() override;

public slots:

	void mill(BasicItems *item);

signals:

	void finish_mill(BasicItems *item1);

private:
	ItemGetter *getter;
	ItemSender *sender;
};
#endif //PROJDRILL_MACHINEBALLMILL_H
