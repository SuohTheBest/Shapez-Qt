#ifndef SAVEWIDGET_H
#define SAVEWIDGET_H

#include <QWidget>

namespace Ui {
	class SaveWidget;
}

class SaveWidget : public QWidget {
Q_OBJECT

public:
	explicit SaveWidget(QWidget *parent = nullptr);

	~SaveWidget();
public slots:
    void button_clicked_1();
    void button_clicked_2();
    void button_clicked_3();
    void button_clicked_4();
signals:
    void send_data(short data_chosen);
private:
	Ui::SaveWidget *ui;
    short data_chosen;
};

#endif // SAVEWIDGET_H
