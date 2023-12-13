#include "menuwidget.h"
#include "ui_menuwidget.h"
#include "./src/action/savewidget.h"
#include "./src/action/levelup.h"
#include "./src/map/MapCreator.h"

MenuWidget::MenuWidget(QWidget *parent) :
		QWidget(parent), ui(new Ui::MenuWidget) {
	ui->setupUi(this);
	connect(ui->button_start_game, SIGNAL(clicked()), this, SLOT(start_game()));
	connect(ui->button_exit, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(ui->button_load_game, SIGNAL(clicked()), this, SLOT(load_game()));
	connect(ui->button_open_shop, SIGNAL(clicked()), this, SLOT(open_shop()));
	this->resize(1123, 855);

}

MenuWidget::~MenuWidget() {
	delete ui;
}

void MenuWidget::start_game() {
	emit game_start();
}

void MenuWidget::load_game() {
	SaveWidget *savewidget = new SaveWidget();
	savewidget->check_is_selectable();
	savewidget->show();
	connect(savewidget, SIGNAL(send_data(short)), this, SLOT(load_game_selected(short)));
}

void MenuWidget::load_game_selected(short chosen) {
	emit game_load(chosen);
}

void MenuWidget::open_shop() {
	LevelUp *levelup = new LevelUp("全局强化", "强化交付中心的大小\n(将交付中心的大小\n增加1)",
								   "开采物所在地块的数量\n(将开采物所在的地块\n增加10",
								   "获得的金币数量\n(获得的金币数量\n增加1)");
	levelup->check_selectable();
	levelup->show();
	connect(levelup, SIGNAL(send_levelup(int)), this, SLOT(handle_global_levelup(int)));
}

void MenuWidget::handle_global_levelup(int n) {
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
	int gold = root_obj.value("gold").toInt();
	switch (n) {
		case 1: {
			int selection1 = root_obj.value("selection1_gold").toInt();
			int size = root_obj.value("center_size").toInt();
			gold -= selection1;
			root_obj["gold"] = gold;
			root_obj["center_size"] = size + 1;
			root_obj["selection1_gold"] = selection1 + 20;
			break;
		}
		case 2: {
			int selection2 = root_obj.value("selection2_gold").toInt();
			int coal = root_obj.value("coal_num").toInt();
			gold -= selection2;
			root_obj["gold"] = gold;
			root_obj["coal_num"] = coal + 10;
			root_obj["selection2_gold"] = selection2 + 20;
			MapCreator *creator = new MapCreator();
			creator->level_up(10);
			break;
		}
		case 3: {
			int selection3 = root_obj.value("selection3_gold").toInt();
			int gold_plus = root_obj.value("gold_plus").toInt();
			gold -= selection3;
			root_obj["gold"] = gold;
			root_obj["gold_plus"] = gold_plus + 1;
			root_obj["selection3_gold"] = selection3 + 20;
			break;
		}
		default: {
			break;
		}
	}
	doc.setObject(root_obj);
	if (!save.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Failed to open file";
		return;
	}
	save.write(doc.toJson());
	save.close();
}

