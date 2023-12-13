#ifndef PROJDRILL_SAVEBUTTON_H
#define PROJDRILL_SAVEBUTTON_H

#include "QPushButton"
#include "../machine/MachineBase.h"
#include "../item/ItemsBase.h"
#include "savewidget.h"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"

class SaveButton : public QPushButton {
Q_OBJECT
public:
	SaveButton(short (&map)[64][64], QList<MachineBase *> &machine_list, float *mul_1, float *mul_2, float *mul_3);

public slots:

	void on_clicked();

	void save(short data_chosen);

signals:

	void pause();

	void restart();

private:
	QList<MachineBase *> &machine_list;
	SaveWidget *saveWidget;
	short (&map)[64][64];
	float *mul_1;
	float *mul_2;
	float *mul_3;
};

#endif //PROJDRILL_SAVEBUTTON_H
