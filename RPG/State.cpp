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
	keyTimeMax = 3.f;
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



void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePosGrid = sf::Vector2u{ static_cast<unsigned>(mousePosView.x) / static_cast<unsigned>(gridSize) ,static_cast<unsigned>(mousePosView.y) / static_cast<unsigned>(gridSize)};
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
		std::cout << "true" << std::endl;
		return true;
		
	}
	std::cout << "not true" << std::endl;
	return false;
}


