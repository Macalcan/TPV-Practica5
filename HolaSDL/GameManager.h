#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "SDLGame.h"
#include "GameObject.h"
#include "BallObserver.h"
#include "GameStateObserver.h"
#include "Font.h"
#include "Texture.h"
#include "PingPongPhysics.h"

class GameManager: public GameObject, public BallObserver {

public:
	GameManager(SDLGame* game);
	virtual ~GameManager();

	virtual void registerGameStateObserver(GameStateObserver* o);

	// from GameObject
	virtual void handleInput(const SDL_Event& e);
	virtual void update();
	virtual void render();

	// from BallObserver
	virtual void onCollision(GameObject* ball, GameObject* o);
	virtual void onBorderExit(GameObject* ball, BallObserver::EXIT_SIDE side);

private:
	enum actors {
		playerL, playerR, other
	};
	Font* font_;
	Texture startMsgTexture_;
	Texture points;
	Texture GameState;
	std::vector<GameStateObserver*>obsever_;
	SoundEffect* wallHit_;
	SoundEffect* paddleHit_;
	int pointsL, pointsR;
	SDL_Color color;
	GameStateObserver* pingPongPhysics_;
};

#endif /* SCOREBOARD_H_ */
