#include "PaddleMouseInputComp.h"

PaddleMouseInputComp::PaddleMouseInputComp(unsigned int velocity) {
	velocity_ = velocity;
}

PaddleMouseInputComp::~PaddleMouseInputComp() {

}

void PaddleMouseInputComp::init(GameObject* paddle) {
	paddle->setDirection(0, 0);
}

void PaddleMouseInputComp::handleInput(SDL_Event event, GameObject* paddle) {
	

	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			paddle->setDirectionY(velocity_ * -1);
		}
		else if (event.button.button == SDL_BUTTON_LEFT)
		{
			paddle->setDirectionY(velocity_);
		}
		else if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			paddle->setDirectionY(0);
		}
	}
}
