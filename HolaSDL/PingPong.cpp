#include "PingPong.h"
#include "BounceOnBorders.h"
#include "RectRender.h"
#include "ImageRendered.h"
#include "StopOnBordersPhysics.h"
#include "SimpleMovePhysics.h"
#include "PaddleKeyboardInputComp.h"
#include "PaddleMouseInputComp.h"
#include "PaddleAIPhysics.h"
#include "PingPongPhysics.h"

PingPong::PingPong() :
		SDLGame("Ping Pong", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

PingPong::~PingPong() {
	closeGame();
}

void PingPong::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	SDL_Color color = { 255, 255, 255, 255 };

	rectangleRenderer_ = new RectRender(color);
	imageRenderer_ = new ImageRendered( getResources()->getTexture(SDLGame::TennisBall) );

	bounceOnBorderPhysics_ = new BounceOnBorders(true, true, true, true);
	stopOnBordersPhysics_ = new StopOnBordersPhysics(true, true, true, true);
	
	leftPaddleInput_ = new PaddleKeyboardInputComp(SDLK_a, SDLK_s, SDLK_z, 5);
	rightPaddleInput_ = new PaddleKeyboardInputComp(SDLK_UP, SDLK_DOWN, SDLK_SPACE, 5);
	mousePaddleInput_ = new PaddleMouseInputComp();

	imageKeyboard_ = new ImageRendered(getResources()->getTexture(SDLGame::KeyBoardIcon));
	imageMouse_ = new ImageRendered(getResources()->getTexture(SDLGame::MouseIcon));
	imageIA_ = new ImageRendered(getResources()->getTexture(SDLGame::AIIcon));

	
	// ball
	ball_ = new GameComponent(this);
	ball_->setWidth(10);
	ball_->setHeight(10);
	ball_->setDirection( (rand() % 5)+3, (rand()%5)+3); // change to  (0,0) at the end
	ball_->setPosition(
			ball_->getGame()->getWindowWidth() / 2 - ball_->getWidth() / 2,
			ball_->getGame()->getWindowHeight() / 2 - ball_->getHeight() / 2);
	//  ball_->setPhysicsComponent(bounceOnBorderPhysics_);
	ball_->setRenderComponent(rectangleRenderer_);

	// use the following for an image of a tennis ball
	// ball_->setRenderComponent(imageRenderer_);

	//obstacle
	obstacle_ = new GameComponent(this);
	obstacle_->setRenderComponent(rectangleRenderer_);
	
	// left paddle
	left_paddle_ = new GameComponent(this);
	left_paddle_->setWidth(10);
	left_paddle_->setHeight(60);
	left_paddle_->setPosition(30,
			(getWindowHeight() - left_paddle_->getHeight()) / 2);
	left_paddle_->setDirection(0, 0);
	left_paddle_->setRenderComponent(rectangleRenderer_);

	//physics
	 paddleAIPhysics_ = new PaddleAIPhysics(ball_);

	// right paddle
	right_paddle_ = new GameComponent(this);
	right_paddle_->setWidth(10);
	right_paddle_->setHeight(60);
	right_paddle_->setPosition(getWindowWidth() - 40,
			(getWindowHeight() - right_paddle_->getHeight()) / 2);
	right_paddle_->setDirection(0, 0);
	right_paddle_->setRenderComponent(rectangleRenderer_);

	switcherLeft_ = new ComponentSwitcher(this, left_paddle_, SDLK_1);
	switcherRight_ = new ComponentSwitcher(this, right_paddle_, SDLK_2);

	switcherLeft_->addMode(leftPaddleInput_, stopOnBordersPhysics_, rectangleRenderer_, imageKeyboard_);
	switcherLeft_->addMode(mousePaddleInput_, stopOnBordersPhysics_, rectangleRenderer_, imageMouse_);
	switcherLeft_->addMode(nullptr, paddleAIPhysics_, rectangleRenderer_, imageIA_);
	switcherLeft_->setMode(0);
	switcherLeft_->setPosition(10, 10);
	switcherLeft_->setWidth(50);
	switcherLeft_->setHeight(50);

	switcherRight_->addMode(rightPaddleInput_, stopOnBordersPhysics_, rectangleRenderer_, imageKeyboard_);
	switcherRight_->addMode(mousePaddleInput_, stopOnBordersPhysics_, rectangleRenderer_, imageMouse_);
	switcherRight_->addMode(nullptr, paddleAIPhysics_, rectangleRenderer_, imageIA_);
	switcherRight_->setMode(0);
	switcherRight_->setPosition(getWindowWidth() - 60, 10);
	switcherRight_->setWidth(50);
	switcherRight_->setHeight(50);
	
	pingPongPhysics_ = new PingPongPhysics(left_paddle_, right_paddle_);
	ball_->setPhysicsComponent(pingPongPhysics_);

	// game manager
	gameManager_ = new GameManager(this, left_paddle_, right_paddle_);

	timedObstacle_ = new TimedObstacle(this, 30000, 3000, ball_);
	timedObstacle_->addObserver(gameManager_);

	pingPongPhysics_->resgisterBallObserver(gameManager_);
	gameManager_->registerGameStateObserver(pingPongPhysics_);


	actors_.push_back(switcherLeft_);
	actors_.push_back(switcherRight_);
	actors_.push_back(left_paddle_);
	actors_.push_back(right_paddle_);
	actors_.push_back(ball_);
	actors_.push_back(gameManager_);
	actors_.push_back(timedObstacle_);
}

void PingPong::closeGame() {
	delete right_paddle_;
	delete left_paddle_;
	delete ball_;
	delete rectangleRenderer_;
	delete imageRenderer_;
	delete bounceOnBorderPhysics_;
	delete stopOnBordersPhysics_;
	delete leftPaddleInput_;
	delete rightPaddleInput_;
	delete mousePaddleInput_;
	delete paddleAIPhysics_;
	delete pingPongPhysics_;
	delete timedObstacle_;
}

void PingPong::start() {
	exit_ = false;
	while (!exit_) {
		handleInput();
		update();
		render();
		SDL_Delay(10);
	}
}

void PingPong::stop() {
	exit_ = true;
}

void PingPong::update() {
	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->update();
	}
}

void PingPong::handleInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (unsigned int i = 0; i < actors_.size(); i++) {
			actors_[i]->handleInput(event);
		}

	}
}

void PingPong::render() {
	SDL_SetRenderDrawColor(getRenderer(), 0, 100, 100, 255);  // Dark grey.
	SDL_RenderClear(getRenderer());

	for (unsigned int i = 0; i < actors_.size(); i++) {
		actors_[i]->render();
	}

	SDL_RenderPresent(getRenderer());
}

