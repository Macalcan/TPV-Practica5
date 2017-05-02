#include <cmath>
#include <random>
#include "PingPongPhysics.h"
using namespace std;

PingPongPhysics::PingPongPhysics(GameObject* left_paddle,
		GameObject* right_paddle) :
		left_paddle_(left_paddle), right_paddle_(right_paddle), hits_(
				0), speed_(8), stateRound(false) {
}

PingPongPhysics::~PingPongPhysics() {
}

void PingPongPhysics::init(GameObject* o) {

	o->setDirection(0, 0);
	o->setPosition(o->getGame()->getWindowWidth() / 2 - o->getWidth(), o->getGame()->getWindowHeight() / 2 - o->getHeight() / 2);
}


void PingPongPhysics::update(GameObject* o) {

	if (!stateRound)
	{
		if (o->getDirection().getX() == 0 && o->getDirection().getY() == 0) {
			int sign = o->getDirection().getX() < 0 ? 1 : -1;
			int rel_y = (o->getPosition().getY() - o->getPosition().getY() + o->getHeight());
			float angle = (2.14f * rel_y - 75.0f);
			int dx = sign * speed_ * std::cos(angle * M_PI / 180.0f);
			int dy = speed_ * std::sin(angle * M_PI / 180.0f);
			o->setDirection(dx, dy);
		}

		Vector2D<int> nextPos = o->getPosition() + o->getDirection();
		GameObject* paddle = nullptr; //paddle that hits the ball
		bool paddleHit = false; //bool to see if a paddle has been hit
		BallObserver::EXIT_SIDE eSide; //side the ball collides with
		bool wallHit = false; //bool to see if a wall has been hit

		//collisions with walls

		if (nextPos.getX() <= 0)
		{
			nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
			o->setPosition(nextPos);
			o->setDirectionY(o->getDirection().getY() * -1);
			for (int i = 0; i < observers.size(); i++)
			{
				observers[i]->onBorderExit(o, BallObserver::LEFT);
			}
			
		}
		else if (nextPos.getX() >= o->getGame()->getWindowWidth())
		{
			nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
			o->setPosition(nextPos);
			o->setDirectionY(o->getDirection().getY() * -1);
			for (int i = 0; i < observers.size(); i++)
			{
				observers[i]->onBorderExit(o, BallObserver::RIGHT);
			}
		}
		else if (nextPos.getY() <= 0)
		{
			nextPos.setY(0);
			o->setPosition(nextPos);
			o->setDirectionY(o->getDirection().getY() * -1);
			for (int i = 0; i < observers.size(); i++)
			{
				observers[i]->onCollision(o, nullptr);
			}
		}
		else if (nextPos.getY() >= o->getGame()->getWindowHeight() - o->getHeight())
		{
			nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
			o->setPosition(nextPos);
			o->setDirectionY(o->getDirection().getY() * -1);
			for (int i = 0; i < observers.size(); i++)
			{
				observers[i]->onCollision(o, nullptr);
			}

		}

		//if (wallHit)
		//{
		//	nextPos.setY(o->getGame()->getWindowHeight() - o->getHeight());
		//	o->setPosition(nextPos);
		//	o->setDirectionY(o->getDirection().getY() * -1);
		//	for (int i = 0; i < observers.size(); i++)
		//	{
		//		observers[i]->onBorderExit(o, eSide);
		//	}
		//}

		//collisions with paddles

		if (nextPos.getX() >= left_paddle_->getPosition().getX() && nextPos.getX() <= (left_paddle_->getPosition().getX() + left_paddle_->getWidth())
			&& nextPos.getY() >= left_paddle_->getPosition().getY() && nextPos.getY() <= (left_paddle_->getPosition().getY() + left_paddle_->getHeight()))
		{
			hits_++;
			paddleHit = true;
			paddle = left_paddle_;
		}
		else if (nextPos.getX() >= right_paddle_->getPosition().getX() && nextPos.getX() <= (right_paddle_->getPosition().getX() + right_paddle_->getWidth())
			&& nextPos.getY() >= right_paddle_->getPosition().getY() && nextPos.getY() <= (right_paddle_->getPosition().getY() + right_paddle_->getHeight()))
		{
			hits_++;
			paddleHit = true;
			paddle = right_paddle_;
		}

		if (paddleHit)
		{
			for (int i = 0; i < observers.size(); i++)
			{
				observers[i]->onCollision(o, paddle);
			}
			int sign = o->getDirection().getX() < 0 ? 1 : -1;
			int rel_y = (o->getPosition().getY() - paddle->getPosition().getY() + o->getHeight());
			float angle = (2.14f * rel_y - 75.0f);
			int dx = sign * speed_ * std::cos(angle * M_PI / 180.0f);
			int dy = speed_ * std::sin(angle * M_PI / 180.0f);
			o->setDirection(dx, dy);
		}

		if (hits_ == 5)
		{
			hits_ = 0;
			speed_++;
		}


		o->setPosition(nextPos);
	}

	else {

		o->setDirection(0, 0);
		o->setPosition((o->getGame()->getWindowWidth() - o->getWidth()) / 2, (o->getGame()->getWindowWidth() - o->getWidth()) / 2);

	}
}


void PingPongPhysics::resgisterBallObserver(BallObserver* o) {
	bool search = false;

	int i = 0;
	while (i < observers.size() && !search)
	{
		if (observers[i] == o)
			search = true;
	}

	if (!search)
		observers.emplace_back(o);
}


void PingPongPhysics::onGameStart() {
	hits_ = 0;
	speed_ = 8;
	stateRound = false;
}

void PingPongPhysics::onGameOver() {
	stateRound = true;
}

void PingPongPhysics::onRoundStart() {
	onGameStart();
}

void PingPongPhysics::onRoundOver() {
	onGameOver();
}

