#include "PaddleAIPhysics.h"
using namespace std;

PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
		ball_(ball) {
}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::init(GameObject* paddle) {
	paddle->setDirectionY(3);
}

void PaddleAIPhysics::update(GameObject* paddle) {

	Vector2D<int> dirBall = ball_->getDirection();
	Vector2D<int> posPaddle = paddle->getPosition();
	Vector2D<int> y_pred = ball_->getPosition() + ball_->getDirection();
	int posBall = ball_->getPosition().getX();

	
	if (dirBall.getX() < 0)
	{	
		if (posPaddle.getY() + paddle->getHeight() / 2 == paddle->getGame()->getWindowHeight() / 2
			|| posPaddle.getY() == paddle->getGame()->getWindowHeight() / 2 - paddle->getHeight() / 2)
		{
			paddle->setDirectionY(0);
		}
		else if (posPaddle.getY() > paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(3 * -1);
		}
		else if (posPaddle.getY() < paddle->getGame()->getWindowHeight() / 2 - paddle->getHeight() / 2)
		{
			paddle->setDirectionY(5);
		}
		
	}
	else
	{
		if (posPaddle.getY() == 0)
		{
			paddle->setDirectionY(5);
		}
		else if (posPaddle.getY() == paddle->getGame()->getWindowHeight() - paddle->getHeight()/2)
		{
			paddle->setDirectionY(5 * -1);
		}
		else if (y_pred.getY() > paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(5 * -1);
		}
		else if (y_pred.getY() < paddle->getGame()->getWindowHeight() / 2)
		{
			paddle->setDirectionY(3);
		}

	}
	paddle->setPosition(paddle->getPosition() + paddle->getDirection()); 

}

