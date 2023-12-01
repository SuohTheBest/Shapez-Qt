#include "RotateButton.h"

RotateButton::RotateButton(MachineShadow *shadow) :
		shadow(shadow), QPushButton() {
	this->setIcon(QIcon("./img/button/rotate.png"));
	this->setEnabled(false);
    connect(this, &RotateButton::clicked, this, &RotateButton::on_clicked);
}

void RotateButton::on_clicked() {
	shadow->rotate();
}

void RotateButton::set_shadow(MachineShadow *shadow) {
	this->shadow = shadow;
}

void RotateButton::set_enable(MachineShadow *shadow) {
	this->shadow = shadow;
	this->setEnabled(true);
}

void RotateButton::set_disable() {
	delete this->shadow;
	this->shadow = nullptr;
}
