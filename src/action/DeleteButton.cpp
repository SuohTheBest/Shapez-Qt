#include "DeleteButton.h"

DeleteButton::DeleteButton(QWidget *parent) : QPushButton(parent) {
	this->setToolTip("删除");
	this->setFixedSize(QSize(144, 144));
	this->setIcon(QIcon("./img/button/bomb.png"));
	this->setCheckable(true);

}

