#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"
using namespace std;

GameManager::GameManager(SDLGame* game, GameObject* left_paddle, GameObject* right_paddle) :
GameObject(game), pointsL(0), pointsR(0), left_paddle(left_paddle), right_paddle(right_paddle),powerUpPared({ 1111, 0, 10, game->getWindowHeight() }) {
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);
	color = { 255, 255, 255, 255 };
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
	
	pointsL = pointsR = 0;
	wallHit_ = game->getResources()->getSoundEffect(game->Wall_Hit);
	paddleHit_ = game->getResources()->getSoundEffect(game->Paddle_Hit);
	last_paddle_hit = nullptr;
	obsState = false;
	obsR = false;
	obsL = false;
}

GameManager::~GameManager() {
}



void GameManager::update() {

	points.loadFromText(getGame()->getRenderer(),
		std::string(std::to_string(pointsR) + " - " + std::to_string(pointsL)),
		*font_, color);
	
	
}

void GameManager::handleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			if (pointsL == 0 && pointsR == 0 || pointsL == 5 || pointsR == 5)
			{
				// pingPongPhysics_->init(ba)
				pingPongPhysics_->onGameStart();
				pointsL = 0;
				pointsR = 0;
			}
			else
				pingPongPhysics_->onRoundStart();
			GameState.close();
			startMsgTexture_.close();
		}
	}
}

void GameManager::render() {

	// just an example, should be adjusted to the requirements!
	points.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - points.getWidth()) / 2, getGame()->getWindowHeight() - 20);
	GameState.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - points.getWidth()) / 2, getGame()->getWindowHeight() - 60);
	startMsgTexture_.render(getGame()->getRenderer(), (getGame()->getWindowWidth()-startMsgTexture_.getWidth())/ 2, getGame()->getWindowHeight()-40);
	

	if (obsL || obsR)
	{

		SDL_RenderFillRect(game_->getRenderer(), &powerUpPared);
	}
	
}

void GameManager::onCollision(GameObject* ball, GameObject* o) {

	if (o == nullptr){
		//wallHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Wall_Hit);
		wallHit_->play();
	}
	else {
		//paddleHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Paddle_Hit);
		paddleHit_->play();
		last_paddle_hit = o;
	}
}

void GameManager::onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side) {

	switch (side) {
	case LEFT:
		if (!obsL)
		{

			if (pointsL < 5){
				pointsL++;
				pingPongPhysics_->onRoundOver();
			}
			update();
			startMsgTexture_.loadFromText(getGame()->getRenderer(),
				"Press Space to Start", *font_, color);
			last_paddle_hit = nullptr;

			if (pointsL == 5){
				GameState.loadFromText(game_->getRenderer(), "playerR won", *font_, color);
				pingPongPhysics_->onGameOver();
			}
		}
		
		
		break;
	case RIGHT:
		if (!obsR)
		{

			if (pointsR < 5){
				pointsR++;
				pingPongPhysics_->onRoundOver();
			}

			update();
			startMsgTexture_.loadFromText(getGame()->getRenderer(),
				"Press Space to Start", *font_, color);
			last_paddle_hit = nullptr;

			if (pointsR == 5){
				GameState.loadFromText(game_->getRenderer(), "playerL won", *font_, color);
				pingPongPhysics_->onGameOver();
			}
		}
		
		break;
	case TOP: case BOT:
		wallHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Wall_Hit);
		wallHit_->play();
		break;
	default:
		break;
	}

	

}

void GameManager::registerGameStateObserver(GameStateObserver* o) {
	pingPongPhysics_ = o;
}

void GameManager::onObstacleStateChange(GameObject* obs, bool state) {
	if (!state) {
		powerUpPared.x = -1111;
		obs->setActive(false);
		obsL = false;
		obsR = false;
	}
	else
	{
		obsState = state;
	}
}

void GameManager::onObstacleCollision(GameObject* obs, GameObject* o) {
	if (obs != nullptr)
	{

		if (last_paddle_hit->getPosition().getX() > getGame()->getWindowWidth() / 2) {
			powerUpPared.x = game_->getWindowWidth() - powerUpPared.w;
			obsR = true;
		}

		else {
			powerUpPared.x = 0;
			obsL = true;
		}

		wallHit_->play();
	}
}