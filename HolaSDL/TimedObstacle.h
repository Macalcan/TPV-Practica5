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

	virtual void onObstacleStateChange(GameObject* obs, bool state);
	virtual void onObstacleCollision(GameObject* obs, GameObject* o);

	virtual void update();
	virtual void render() const;

	virtual void onGameStart();
	virtual void onGameOver();
	virtual void onRoundStart();
	virtual void onRoundOver();

private:
	int m_pTime, m_dTime, m_TimePassing;

	bool activated;
	
	std::vector<TimedObstacleObserver*> observers;

	
};
#endif

