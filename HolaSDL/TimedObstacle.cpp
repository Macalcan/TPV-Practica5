#include "TimedObstacle.h"


TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : GameObject(game), m_pTime(pTime), m_dTime(dTime)
{
	m_TimePassing = 0;
	activated = false;
}


TimedObstacle::~TimedObstacle()
{
}

void TimedObstacle::addObserver(TimedObstacleObserver* o) {
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

void TimedObstacle::onGameStart(){
	onRoundStart();
}

void TimedObstacle::onGameOver(){
	onRoundOver();
}

void TimedObstacle::onRoundStart(){
	setActive(true);
}

void TimedObstacle::onRoundOver(){
	setActive(false);
}

void TimedObstacle::update(){
	m_TimePassing++;
	if (isActive && !activated)
	{
		if (m_TimePassing == m_pTime)
		{
			m_TimePassing = 0;
			if (rand() % 2 == 0)
			{
				activated = true;
			}
		}
	}
	
	else if (activated)
	{
		if (m_TimePassing == m_dTime)
		{
			m_TimePassing = 0;
			activated = false;
		}
	}
}