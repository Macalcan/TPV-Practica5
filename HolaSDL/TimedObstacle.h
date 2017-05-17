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
	
private:
	int m_pTime, m_dTime;
};
#endif

