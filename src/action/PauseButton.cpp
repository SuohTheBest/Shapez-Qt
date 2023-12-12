#include "PauseButton.h"

PauseButton::PauseButton() :
		QPushButton() {
	this->setToolTip("暂停");
	this->setFixedSize(QSize(144, 144));
	this->setIcon(QIcon("./img/button/pause.png"));
	this->setEnabled(true);
	this->is_pause = false;
}

void PauseButton::switch_state() {
	if (!this->is_pause) {
		this->setToolTip("开始");
		this->setIcon(QIcon("./img/button/restart.png"));
		this->is_pause = true;
	} else {
		this->setToolTip("暂停");
		this->setIcon(QIcon("./img/button/pause.png"));
		this->is_pause = false;
	}
}
