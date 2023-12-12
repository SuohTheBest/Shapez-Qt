#include "BackToMenu.h"

BackToMenuButton::BackToMenuButton() :
		QPushButton() {
	this->setToolTip("返回主菜单");
	this->setFixedSize(QSize(144, 144));
	this->setIcon(QIcon("./img/button/menu.png"));
	this->setEnabled(true);
}