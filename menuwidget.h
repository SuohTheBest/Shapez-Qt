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

signals:
    void game_start();

private:
	Ui::MenuWidget *ui;
};

#endif // MENUWIDGET_H
