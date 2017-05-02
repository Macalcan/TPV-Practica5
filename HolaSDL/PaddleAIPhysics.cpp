#include "PaddleAIPhysics.h"
using namespace std;

PaddleAIPhysics::PaddleAIPhysics(GameObject* ball) :
ball_(ball) {
}

PaddleAIPhysics::~PaddleAIPhysics() {
}

void PaddleAIPhysics::init(GameObject* paddle) {
	paddle->setDirectionY(10);
}

void PaddleAIPhysics::update(GameObject* paddle) {

	Vector2D<int> dirBall = ball_->getDirection();
	Vector2D<int> posPaddle = paddle->getPosition();
	Vector2D<int> y_pred = ball_->getPosition() + ball_->getDirection();
	int posBall = ball_->getPosition().getX();


	if (dirBall.getX() < 0)
	{

		
		if (posPaddle.getX() > paddle->getGame()->getWindowWidth() / 2) {
			// Mitad superior
			if (posPaddle.getY() + paddle->getHeight() / 2 < paddle->getGame()->getWindowHeight() / 2) {
				vDir = 1;
			}
			// Mitad inferior
			else if (posPaddle.getY() + paddle->getHeight() / 2 > paddle->getGame()->getWindowHeight() / 2)
			{
				vDir = -1;
			}
			else {
				vDir = 0;
			}
			paddle->setDirectionY(vDir * 12);

		}

		
		else {
			if (posPaddle.getY() + paddle->getHeight() / 2
				< ball_->getPosition().getY() - paddle->getHeight() / 2) {
				vDir = 1;
			}
			else if (posPaddle.getY() + paddle->getHeight() / 2
				> ball_->getPosition().getY() + paddle->getHeight() / 2)
			{
				vDir = -1;
			}
			else {
				vDir = 0;
			}
			paddle->setDirectionY(vDir * 12);
		}

	}
	else
	{

		
		if (posPaddle.getX() > paddle->getGame()->getWindowWidth() / 2) {

			if (posPaddle.getY() + paddle->getHeight() / 2
				< ball_->getPosition().getY() - paddle->getHeight() / 2) {
				vDir = 1;
			}
			else if (posPaddle.getY() + paddle->getHeight() / 2
				> ball_->getPosition().getY() + paddle->getHeight() / 2)
			{
				vDir = -1;
			}
			else {
				vDir = 0;
			}
			paddle->setDirectionY(vDir * 12);
		}

		
		else {

			// Mitad superior
			if (posPaddle.getY() + paddle->getHeight() / 2 < paddle->getGame()->getWindowHeight() / 2) {
				vDir = 1;
			}
			// Mitad inferior
			else if (posPaddle.getY() + paddle->getHeight() / 2 > paddle->getGame()->getWindowHeight() / 2)
			{
				vDir = -1;
			}
			else {
				vDir = 0;
			}
			paddle->setDirectionY(vDir * 12);
		}

	}
	paddle->setPosition(paddle->getPosition() + paddle->getDirection());

}