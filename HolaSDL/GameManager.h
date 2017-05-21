#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "SDLGame.h"
#include "GameObject.h"
#include "BallObserver.h"
#include "GameStateObserver.h"
#include "Font.h"
#include "Texture.h"
#include "PingPongPhysics.h"
#include "TimedObstacleObserver.h"

class GameManager : public GameObject, public BallObserver, public TimedObstacleObserver {

public:
	GameManager(SDLGame* game, GameObject* left_paddle, GameObject* right_paddle);
	virtual ~GameManager();

	virtual void registerGameStateObserver(GameStateObserver* o);

	// from GameObject
	virtual void handleInput(const SDL_Event& e);
	virtual void update();
	virtual void render();

	// from BallObserver
	virtual void onCollision(GameObject* ball, GameObject* o);
	virtual void onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side);

	// from TimedObstacleObserver
	// Avisa a los observadores cuando se activa/desactiva el obstaculo
	virtual void onObstacleStateChange(GameObject* obs, bool state);
	// Avisa a los observadores que el objeto "o" ha chocado con el obstaculo "obs"
	virtual void onObstacleCollision(GameObject* obs, GameObject* o);

private:


	Font* font_;

	Texture startMsgTexture_;
	Texture points;
	Texture GameState;

	SoundEffect* wallHit_;
	SoundEffect* paddleHit_;

	int pointsL, pointsR;

	SDL_Color color;
	SDL_Rect powerUpPared;

	GameStateObserver* pingPongPhysics_;

	GameObject* left_paddle;
	GameObject* right_paddle;
	

	GameObject* last_paddle_hit;

	bool obsR;
	bool obsL;
	bool obsState;
};

#endif /* SCOREBOARD_H_ */
