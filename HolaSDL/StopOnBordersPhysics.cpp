#include "StopOnBordersPhysics.h"

StopOnBordersPhysics::StopOnBordersPhysics(bool left, bool right, bool top,
		bool bottom) :
		left_(left), right_(right), top_(top), bottom_(bottom) {
}

StopOnBordersPhysics::~StopOnBordersPhysics() {
}

void StopOnBordersPhysics::init(GameObject* o) {
	
}


void StopOnBordersPhysics::update(GameObject* o) {
	Vector2D<int> position = o->getPosition() + o->getDirection();

	if (left_ && position.getX() <= 0)
	{
		o->setPosition(position.getX() + 5, position.getY());
		o->setDirection(0, 0);
	}
	else if (right_ && position.getX() >= o->getGame()->getWindowHeight)
	{
		o->setPosition(position.getX() - 5, position.getY());
		o->setDirection(0, 0);
	}
	else if (top_ && position.getY <= 0)
	{
		o->setPosition(position.getX(), position.getY() + 5);
		o->setDirection(0, 0);
	}
	else if (bottom_ && position.getY() >= o->getGame()->getWindowHeight)
	{
		o->setPosition(position.getX(), position.getY() - 5);
		o->setDirection(0, 0);
	}
}
