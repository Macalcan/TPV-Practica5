#ifndef PADDLEMOUSEINPUTCOMP_H_
#define PADDLEMOUSEINPUTCOMP_H_

#include "InputComponent.h"

class PaddleMouseInputComp: public InputComponent {
public:
	PaddleMouseInputComp(unsigned int velocity);
	virtual ~PaddleMouseInputComp();

	// from InputComponent
	void init(GameObject* paddle);
	void handleInput(SDL_Event e, GameObject* paddle);
protected:
	unsigned int velocity_;
};

#endif /* PADDLEMOUSEINPUTCOMP_H_ */
