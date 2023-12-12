#ifndef PROJDRILL_PAUSEBUTTON_H
#define PROJDRILL_PAUSEBUTTON_H

#include "QPushButton"

class PauseButton : public QPushButton {
public:
	PauseButton();

	void switch_state();

	bool is_pause;
private:

};

#endif //PROJDRILL_PAUSEBUTTON_H
