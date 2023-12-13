#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include "QApplication"
#include "QDesktopWidget"

namespace Ui {
	class MenuWidget;
}

class MenuWidget : public QWidget {
Q_OBJECT

public:
	explicit MenuWidget(QWidget *parent = nullptr);

	~MenuWidget();

public slots:

	void start_game();

	void load_game();

	void open_shop();

	void load_game_selected(short selected);

	void handle_global_levelup(int n);

signals:

	void game_start();

	void game_load(short chosen);

private:
	Ui::MenuWidget *ui;
};

#endif // MENUWIDGET_H
