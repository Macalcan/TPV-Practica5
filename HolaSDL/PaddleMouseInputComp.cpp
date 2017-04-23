#include "PaddleMouseInputComp.h"

PaddleMouseInputComp::PaddleMouseInputComp() {
}

PaddleMouseInputComp::~PaddleMouseInputComp() {

}

void PaddleMouseInputComp::init(GameObject* paddle) {
	paddle->setDirection(0, 0);
}

void PaddleMouseInputComp::handleInput(SDL_Event event, GameObject* paddle) {
	

	int x;
	int y;

	SDL_GetMouseState(&x, &y);

	paddle->setPositionY(y);
}
