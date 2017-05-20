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
	m_TimePassing++; // counts time
	if (isActive && !activated) //if the game is on and there is no obstacle
	{
		if (m_TimePassing == m_pTime) //if pTime has passed 
		{
			m_TimePassing = 0; //restart the time passed
			if (rand() % 2 == 0)
			{
				activated = true; //activates the obstacle
				randomPos();
			}
		}
	}
	
	else if (activated) //if there is an obstacle
	{
		if (m_TimePassing == m_dTime) //if it's time to deactivate the obstacle
		{
			m_TimePassing = 0; //restart the time passed
			activated = false; //deactivate the obstacle
		}
	}
}

void TimedObstacle::randomPos(){
	
	setWidth(50); //obstacle's width
	setHeight(50); //obstacle's height
	setPositionY(rand() % game_->getWindowHeight()); //random Y position
	setPositionX(rand() % game_->getWindowWidth()); //random X position
}

void TimedObstacle::render() const{
	SDL_Rect{};
}