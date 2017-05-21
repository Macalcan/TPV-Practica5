#include "TimedObstacle.h"
using namespace std;

TimedObstacle::TimedObstacle(SDLGame* game, int pTime, int dTime, GameObject* ball) : GameObject(game), m_pTime(pTime), m_dTime(dTime), m_ball(ball)
{
	m_TimePassing = 0;
	activated = false;
	cout << m_pTime;
	cout << "I'm active";
	
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

	if (!search){
		observers.emplace_back(o);
		cout << " The observer has been added";
	}
}

void TimedObstacle::onGameStart(){
	setActive(true);
	m_TimePassing = SDL_GetTicks();
}

void TimedObstacle::onGameOver(){
	setActive(false);
}

void TimedObstacle::onRoundStart(){
	onGameStart();

}

void TimedObstacle::onRoundOver(){
	onGameOver();
}

void TimedObstacle::update(){
	int pass = SDL_GetTicks() - m_TimePassing;
	if (isActive()){
		if (activated &&
			!(getPosition().getX() > m_ball->getPosition().getX() + m_ball->getWidth() || getPosition().getX() + getWidth() < m_ball->getPosition().getX()
			|| getPosition().getY() > m_ball->getPosition().getY() + m_ball->getHeight() || getPosition().getY() + getHeight() < m_ball->getPosition().getY()))
		{
			activated = false;
			m_ball->setDirectionX(m_ball->getDirection().getX()*-1);
			onObstacleCollision();

		}
		if (pass > m_pTime){
			onObstacleStateChange(false);
			m_TimePassing += pass;
		}
	}
	else{
		if (pass > m_dTime){
			onObstacleStateChange(true);
			m_TimePassing += pass;
		}

	}
}



void TimedObstacle::render() {
	SDL_Color color_ = { 255, 255, 255, 255 };
	const Vector2D<int> &pos = getPosition();
	SDLGame* game = getGame();
	SDL_Renderer* renderer = game->getRenderer();

	SDL_Rect rect = { pos.getX(), pos.getY(), getWidth(), getHeight() };

	SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
	if (activated)
		SDL_RenderFillRect(renderer, &rect);
}

void TimedObstacle::onObstacleStateChange(bool state){
	if (state) {
		setWidth(25);
		setHeight(300);
		setPosition(game_->getWindowWidth() / 2 - 100 + rand() % 200, rand() % (game_->getWindowHeight() - getHeight()));
		setActive(true);
		activated = true;
		
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

void TimedObstacle::onObstacleCollision(){
	
	//if (getPosition().getX() >= m_ball->getPosition().getX() + m_ball->getWidth() || getPosition().getX() + getWidth() <= m_ball->getPosition().getX()
		//|| getPosition().getY() >= m_ball->getPosition().getY() + m_ball->getHeight() || getPosition().getY() + getHeight() <= m_ball->getPosition().getY())
	//{
		//cout << "COLLISION";
		for (int i = 0; i < observers.size(); i++)
		{
			observers[i]->onObstacleCollision(this, m_ball);
		}
	//}
	
}