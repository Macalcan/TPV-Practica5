#include <string>
#include <cmath>
#include <random>

#include "GameManager.h"


GameManager::GameManager(SDLGame* game) :
		GameObject(game), pointsL(0), pointsR(0) {
	font_ = game_->getResources()->getFont(SDLGame::NESChimera16);
	color = { 255, 255, 255, 255 };
	startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
	obsever_.reserve(10);
	wallHit_ = game->getResources()->getSoundEffect(game->Wall_Hit);
	paddleHit_ = game->getResources()->getSoundEffect(game->Paddle_Hit);
	
}

GameManager::~GameManager() {
}

void GameManager::update() {

	points.loadFromText(getGame()->getRenderer(),
		std::string(std::to_string(pointsL) + " - " + std::to_string(pointsR)),
		*font_, color);
}

void GameManager::handleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			if (pointsL == pointsR == 0) StartGame();
			else StartRound();

			GameState.close();
			startMsgTexture_.close();
		}
	}
}

void GameManager::render() {

	// just an example, should be adjusted to the requirements!
	points.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - points.getWidth()) / 2, getGame()->getWindowHeight() - 20);
	GameState.render(getGame()->getRenderer(), (getGame()->getWindowWidth() - points.getWidth()) / 2, getGame()->getWindowHeight() - 40);
	startMsgTexture_.render(getGame()->getRenderer(), (getGame()->getWindowWidth()-startMsgTexture_.getWidth())/ 2, getGame()->getWindowHeight()-40);
}

void GameManager::onCollision(GameObject* ball, GameObject* o) {

	if (o == nullptr){
		wallHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Wall_Hit);
		wallHit_->play();
	}
	
	else {
		paddleHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Paddle_Hit);
		paddleHit_->play();
	}
}

void GameManager::onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side) {

	switch (side) {
	case LEFT:
		GameState.loadFromText(game_->getRenderer(), "playerL", *font_, color);
		update();
		startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
		pointsL++;
		break;
	case RIGHT:
		GameState.loadFromText(game_->getRenderer(), "playerR", *font_, color);
		update();
		startMsgTexture_.loadFromText(getGame()->getRenderer(),
			"Press Space to Start", *font_, color);
		pointsR++;
		break;
	case TOP: case BOT:
		wallHit_ = ball->getGame()->getResources()->getSoundEffect(SDLGame::Wall_Hit);
		wallHit_->play();
		break;
	}

	

}

void GameManager::registerGameStateObserver(GameStateObserver* o) {
	pingPongPhysics_ = o;
}

void GameManager::StartGame() {
	for (auto obj : obsever_)
		obj->onGameStart();

	update();
}

void GameManager::StartRound() {
	for (auto obj : obsever_)
		obj->onRoundStart();
}

void GameManager::EndGame() {
	for (auto obj : obsever_)
		obj->onGameOver();
	pointsL = pointsR = 0;
}

void GameManager::EndRound() {
	for (auto obj : obsever_)
		obj->onRoundOver();
}
