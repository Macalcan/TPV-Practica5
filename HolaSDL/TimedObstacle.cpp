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
	m_TimePassing = SDL_GetTicks();

}

void TimedObstacle::onRoundOver(){
	setActive(false);
}

void TimedObstacle::update(){
	m_TimePassing++; // counts time
	m_pTime = SDL_GetTicks() - m_TimePassing;
	if (isActive() && !activated) //if the game is on and there is no obstacle
	{
		if (m_TimePassing == m_pTime) //if pTime has passed 
		{
			m_TimePassing = 0; //restart the time passed
			if (rand() % 2 == 0)
			{
				activated = true; //activates the obstacle
				onObstacleStateChange(this, false);
			
			}
		}
	}
	
	else if (activated) //if there is an obstacle
	{
		if (m_TimePassing == m_dTime) //if it's time to deactivate the obstacle
		{
			onObstacleStateChange(this, true);
			m_TimePassing = 0; //restart the time passed
			activated = false; //deactivate the obstacle
		}
	}
}



void TimedObstacle::render() const{
	render();
	
}

void TimedObstacle::onObstacleStateChange(GameObject* obs, bool state){
	if (state) {
		setWidth(50);
		setHeight(50);
		setPosition(game_->getWindowWidth() / 2 - 100 + rand() % 200, rand() % (game_->getWindowHeight() - getHeight()));
		setActive(true);
		activated = false;
	}
	else {
		setActive(false);
		activated = false;
	}
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->onObstacleStateChange(this, state);
	}

}

void TimedObstacle::onObstacleCollision(GameObject* obs, GameObject* o){
	
	for (int i = 0; i < observers.size(); i++)
	{
		observers[i]->onObstacleCollision(this, obs); 
	}
}