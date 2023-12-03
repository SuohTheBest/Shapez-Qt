#include "RotateButton.h"

RotateButton::RotateButton(MachineShadow *shadow) :
         QPushButton(),shadow(shadow) {
	this->setIcon(QIcon("./img/button/rotate.png"));
    this->setIconSize(QSize(64,64));
	this->setEnabled(false);
    connect(this, &RotateButton::clicked, this, &RotateButton::on_clicked);
}

void RotateButton::on_clicked() {
	shadow->rotate();
}

void RotateButton::set_shadow(MachineShadow *shadow) {
	this->shadow = shadow;
}

void RotateButton::set_enable(QPointF pos, int machine_id) {
	shadow->setup(pos,machine_id);
	this->setEnabled(true);
}

void RotateButton::set_disable() {
    this->setEnabled(false);
    shadow->destory();
}
