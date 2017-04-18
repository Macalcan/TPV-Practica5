#include "PaddleAIPhysics.h"
using namespace std;

PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
		ball_(ball) {
}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::init(GameObject* paddle) {
}

void PaddleAIPhysics::update(GameObject* paddle) {

	Vector2D<int> dirBall = ball_->getDirection();
	Vector2D<int> posPaddle = paddle->getPosition();
	Vector2D<int> y_pred = ball_->getPosition() + ball_->getDirection();

	if (dirBall.getX() < 0)
	{
		//cout << "I don't see the ball";

		if (posPaddle.getY() >= paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(5 * -1);
		}
		else if (posPaddle.getY() <= paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(5);
		}
	}
	else
	{
		//cout << "I see the ball";
		if (y_pred.getY() >= paddle->getGame()->getWindowHeight() / 2)
		{
			cout << "I'm moving";
			paddle->setDirectionY(5 * -1);
		}
		else if (y_pred.getY() <= paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(5);
		}

	}
}

