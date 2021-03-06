#include "ComponentSwitcher.h"

ComponentSwitcher::ComponentSwitcher(SDLGame* game, GameComponent* actor,
	SDL_Keycode ctrlKey) :
	GameObject(game), actor_(actor), ctrlKey_(ctrlKey) {

	currMode_ = 0;
}

ComponentSwitcher::~ComponentSwitcher() {
}

void ComponentSwitcher::update() {
}

void ComponentSwitcher::handleInput(const SDL_Event& event) {

	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == ctrlKey_) {
		switchToNext();
	}
}

void ComponentSwitcher::addMode(InputComponent* inputComp,
	PhysicsComponent* physicsComp, RenderComponent* renderComp,
	RenderComponent* modeRendered) {

	inputComps_.push_back(inputComp);
	physicsComp_.push_back(physicsComp);
	modeRenderedComp_.push_back(modeRendered);

}

void ComponentSwitcher::setMode(int mode) {
	currMode_ = mode;
	actor_->setInputComponent(inputComps_[currMode_]);
	actor_->setPhysicsComponent(physicsComp_[currMode_]);
}

void ComponentSwitcher::switchToNext() {
	setMode((currMode_ + 1) % inputComps_.size());

}

void ComponentSwitcher::render() {

	modeRenderedComp_[currMode_]->render(this);
}
