#include <cmath>
#include <random>
#include "PingPongPhysics.h"
using namespace std;

PingPongPhysics::PingPongPhysics(GameObject* left_paddle,
		GameObject* right_paddle) :
		left_paddle_(left_paddle), right_paddle_(right_paddle), hits_(
				0), speed_(8) {
}

PingPongPhysics::~PingPongPhysics() {
}

void PingPongPhysics::init(GameObject* o) {
	int direction = 1 - 2 * (rand() % 2);
	int angle = 60 - (rand() % 121);
	int dx = direction * speed_ * std::cos(angle * M_PI / 180.0f);
	int dy = speed_ * std::sin(angle * M_PI / 180.0f);	o->setDirection(dx, dy);
}

void PingPongPhysics::update(GameObject* o) {
	Vector2D<int> posBall = o->getPosition();
	Vector2D<int> posLeftP = left_paddle_->getPosition();
	Vector2D<int> posRightP = right_paddle_->getPosition();
	

	if (posBall.getX() <= posLeftP.getX() + left_paddle_->getWidth() && posBall.getY() >= posLeftP.getY()
		&& posBall.getY() >= posLeftP.getY() + left_paddle_->getHeight())
	{
		hits_++;
		cout << hits_;
	}

	if (hits_ == 5)
	{
		hits_ = 0;
		speed_++;
	}

	o->setPosition(o->getPosition() + o->getDirection());
}


void PingPongPhysics::resgisterBallObserver(BallObserver* o) {
	
}


void PingPongPhysics::onGameStart() {
}

void PingPongPhysics::onGameOver() {
}

void PingPongPhysics::onRoundStart() {
}

void PingPongPhysics::onRoundOver() {
}

