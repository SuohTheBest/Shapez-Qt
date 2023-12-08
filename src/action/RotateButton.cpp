#include "RotateButton.h"

RotateButton::RotateButton(MachineShadow *shadow) :
		QPushButton(), shadow(shadow) {
	this->setToolTip("建造");
	this->setFixedSize(QSize(72, 72));
	this->setIcon(QIcon("./img/button/rotate.png"));
	this->setEnabled(false);
	connect(this, &RotateButton::clicked, this, &RotateButton::on_clicked);
}

void RotateButton::on_clicked() {
	if (!is_conveyor)shadow->rotate();
	else {
		conveyor->rotate();
	}
}

void RotateButton::set_shadow(MachineShadow *shadow) {
	this->shadow = shadow;
	is_conveyor = false;
}

void RotateButton::set_enable(QPointF pos, int machine_id) {
	shadow->setup(pos, machine_id);
	is_conveyor = false;
	this->setEnabled(true);
}

void RotateButton::set_disable() {
	this->setEnabled(false);
	conveyor = nullptr;
	if (shadow->is_setup)shadow->destory();
}

void RotateButton::set_conveyor(MachineConveyor *conveyor) {
	this->conveyor = conveyor;
	this->setEnabled(true);
	is_conveyor = true;
}
