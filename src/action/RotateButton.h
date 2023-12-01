#ifndef PROJDRILL_ROTATEBUTTON_H
#define PROJDRILL_ROTATEBUTTON_H

#include "QPushButton"
#include "../item/MachineShadow.h"

class RotateButton : public QPushButton {
public:
	RotateButton(MachineShadow *shadow = nullptr);

	void set_shadow(MachineShadow *shadow);

	void set_enable(MachineShadow *shadow);

	void set_disable();

public slots:

	void on_clicked();

private:
	MachineShadow *shadow;
};

#endif //PROJDRILL_ROTATEBUTTON_H
