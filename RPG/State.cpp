#include "stdafx.h"
#include "State.h"

State::State(StateData* state_Data) {
	State_Data = state_Data;
	this->window = state_Data->window;
	this->supportedKeys = state_Data->supportedKeys;
	states = state_Data->states;
	quit = false;
	paused = false;
	keyTime = 0.f;
	keyTimeMax = 1.f;
	gridSize = state_Data->gridsize;
}

State::~State()
{
}

void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}



void State::updateMousePositions(sf::View* view = nullptr)
{
	
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	if (view) {
		window->setView(*view);
	}
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = sf::Vector2i{ static_cast<int>(mousePosView.x) / static_cast<int>(gridSize) ,static_cast<int>(mousePosView.y) / static_cast<int>(gridSize) };
	window->setView(window->getDefaultView());
}

void State::updateKeyTime(const float dt)
{
	if (keyTime < keyTimeMax) {
		keyTime += 10.f * dt;
	}
}


const bool& State::getQuit() const
{
	return quit;
}

const bool State::getKeyTime()
{
	if (keyTime >= keyTimeMax) {
		std::cout << keyTime << " "<<keyTimeMax<<" " << std::endl;
		keyTime = 0.f;
		
		return true;
		
	}
	
	return false;
}

StateData::StateData() : window{}, supportedKeys{}, states{}, gridsize{}, gfxSettings{}
{
}
