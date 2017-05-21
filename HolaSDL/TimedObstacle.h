#ifndef _H_TimedObstacle_H_
#define _H_TimedObstacle_H_

#include "GameObject.h"
#include "GameStateObserver.h"
#include "TimedObstacleObserver.h"	

// Es un GameStateObserver para poder saber si el juego esta en marcha
class TimedObstacle : public GameObject, public GameStateObserver {
public:
	TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball);
	virtual ~TimedObstacle();
	virtual void addObserver(TimedObstacleObserver* o);

	

	virtual void update();
	virtual void render();
	virtual void handleInput(const SDL_Event& event){}

	virtual void onGameStart();
	virtual void onGameOver();
	virtual void onRoundStart();
	virtual void onRoundOver();

protected:

	void onObstacleStateChange(bool state);
	void onObstacleCollision();

	int m_pTime, m_dTime, m_TimePassing;
	
	bool activated;
	 
	GameObject* m_ball;
	std::vector<TimedObstacleObserver*> observers;

	
};
#endif

