#include "levelup.h"
#include "ui_levelup.h"

LevelUp::LevelUp(QString title, QString choose1, QString choose2, QString choose3, QWidget *parent) :
		QWidget(parent), ui(new Ui::LevelUp) {
	ui->setupUi(this);
	ui->title->setText(title);
	ui->button_choose1->setText(choose1);
	ui->button_choose2->setText(choose2);
	ui->button_choose3->setText(choose3);
	connect(ui->button_choose1, &QPushButton::clicked, this, [this]() { handle_button_clicked(1); });
	connect(ui->button_choose2, &QPushButton::clicked, this, [this]() { handle_button_clicked(2); });
	connect(ui->button_choose3, &QPushButton::clicked, this, [this]() { handle_button_clicked(3); });
}

LevelUp::~LevelUp() {
	delete ui;
}

void LevelUp::handle_button_clicked(int n) {
	emit send_levelup(n);
	close();
	this->deleteLater();
}
