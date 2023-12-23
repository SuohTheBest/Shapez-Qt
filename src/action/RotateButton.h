#ifndef PROJDRILL_ROTATEBUTTON_H
#define PROJDRILL_ROTATEBUTTON_H

#include "QPushButton"
#include "../item/MachineShadow.h"
#include "../machine/MachineConveyor.h"
/**
 * @brief 处理物体旋转的按钮
 */
class RotateButton : public QPushButton {
	Q_OBJECT
public:
	RotateButton(MachineShadow *shadow = nullptr);

	void set_shadow(MachineShadow *shadow);

	void set_enable(QPointF pos, int machine_id);

	void set_disable();

	void set_conveyor(MachineConveyor *conveyor);

public slots:

	void on_clicked();

private:
	MachineShadow *shadow;
	MachineConveyor *conveyor;
	bool is_conveyor;
};

#endif //PROJDRILL_ROTATEBUTTON_H
