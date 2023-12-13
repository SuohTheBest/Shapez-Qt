#include "levelup.h"
#include "ui_levelup.h"
#include "string"

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

void LevelUp::check_selectable() {
	QString path("./data/savedata/save00/save.json");
	QFile save(path);
	if (!save.open(QFile::ReadOnly | QFile::Text)) {
		qDebug() << "Open error";
		return;
	}
	QTextStream stream(&save);
	stream.setCodec("UTF-8");
	QString str = stream.readAll();
	save.close();
	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
		qDebug() << "Json格式错误" << jsonError.error;
		return;
	}
	QJsonObject root_obj = doc.object();
	int selection1=root_obj.value("selection1_gold").toInt();
	int selection2=root_obj.value("selection2_gold").toInt();
	int selection3=root_obj.value("selection3_gold").toInt();
	int gold=root_obj.value("gold").toInt();
    if(gold<selection1){ui->button_choose1->setEnabled(false);ui->label_choose1_gold->setStyleSheet("color: red;");}
    if(gold<selection2){ui->button_choose2->setEnabled(false);ui->label_choose2_gold->setStyleSheet("color: red;");}
    if(gold<selection3){ui->button_choose3->setEnabled(false);ui->label_choose3_gold->setStyleSheet("color: red;");}
    ui->label_gold->setText(QString::fromStdString("金币:"+std::to_string(gold)));
    ui->label_choose1_gold->setText(QString::fromStdString("需要金币:"+std::to_string(selection1)));
    ui->label_choose2_gold->setText(QString::fromStdString("需要金币:"+std::to_string(selection2)));
    ui->label_choose3_gold->setText(QString::fromStdString("需要金币:"+std::to_string(selection3)));
}
