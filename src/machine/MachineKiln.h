#ifndef PROJDRILL_MACHINEKILN_H
#define PROJDRILL_MACHINEKILN_H

#include "MachineBase.h"

class MachineKiln : public QObject, public MachineBase {
Q_OBJECT
public:
	MachineKiln(QGraphicsScene *scene, QPointF &pos, short towards);

	static MachineBase *to_base(QGraphicsScene *scene, QPointF &pos, short towards);

	string detail_info() override;

	bool is_legal(BasicItems *item) override;

	void pause() override;

	void restart() override;

	void set_disable() override;

	void burn();

public slots:

	void pre_burn(BasicItems *item);

signals:

	void finish_burn(BasicItems *item1);

private:
	ItemGetter *getter[2];
	ItemSender *sender;
	BasicItems* coal;
	BasicItems* sand;
};

#endif //PROJDRILL_MACHINEKILN_H