#ifndef _H_TimedObstacleObserver_H_
#define _H_TimedObstacleObserver_H_

#include "GameObject.h"

class TimedObstacleObserver
{
public:

	TimedObstacleObserver();

	virtual ~TimedObstacleObserver();

	// Avisa a los observadores cuando se activa/desactiva el obstaculo
	virtual void onObstacleStateChange(GameObject* obs, bool state) = 0;
	// Avisa a los observadores que el objeto "o" ha chocado con el obstaculo "obs"
	virtual void onObstacleCollision(GameObject* obs, GameObject* o) = 0;
};
#endif
