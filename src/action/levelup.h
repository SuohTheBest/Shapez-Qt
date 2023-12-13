#ifndef LEVELUP_H
#define LEVELUP_H

#include <QWidget>
#include "QString"
#include "QPushButton"
#include "QJsonObject"
#include "QFile"
#include "QDebug"
#include <QJsonDocument>
namespace Ui {
	class LevelUp;
}

class LevelUp : public QWidget {
Q_OBJECT

public:
	explicit LevelUp(QString title, QString choose1, QString choose2, QString choose3, QWidget *parent = nullptr);

	void check_selectable();

	~LevelUp();

public slots:

	void handle_button_clicked(int n);

signals:

	void send_levelup(int n);


private:
	Ui::LevelUp *ui;
};

#endif // LEVELUP_H
