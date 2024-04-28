#include "stdafx.h"
#include "EnemyEditorMode.h"

EnemyEditorMode::EnemyEditorMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data): EditorMode{state_data, the_map,editor_state_data}
{
	initVariables();
	initGUI();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

void EnemyEditorMode::update(const float& dt)
{
	updateGUI(dt);
	updateInput(dt);
}

void EnemyEditorMode::render(sf::RenderTarget& target)
{
	renderGUI(target);
}

void EnemyEditorMode::updateInput(const float& dt)
{
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData.mousePosWindow)))
		{
			tMap->addTile(editorStateData.mousePosGrid->x, editorStateData.mousePosGrid->y, 0, textureRect,type,amount,TimeToSpawn,maxDistance);
		}
				
	}
	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData.mousePosWindow)))
		{
			//if (tMap->checkType(TileTypes::ENEMYSPAWNER,editorStateData.mousePosGrid->x, editorStateData.mousePosGrid->y, 0))
				tMap->removeTile(editorStateData.mousePosGrid->x, editorStateData.mousePosGrid->y, 0, ENEMYSPAWNER);
		}
	}
	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TYPE_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (type > 0) {
				type--;
			}
		}else if (type < 100) {
			type++;
		}
		else {
			type = 100;
		}
	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("AMOUNT_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (amount > 0) {
				amount--;
			}
		}else if (amount < 100) {
			amount++;
		}
		else {
			amount = 100;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TTS_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (TimeToSpawn > 0) {
				TimeToSpawn--;
			}
		}
		else if (TimeToSpawn < 1000) {
			TimeToSpawn++;
		}
		else {
			TimeToSpawn = 1000;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("MD_UP"))) && this->getKeyTime())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			if (maxDistance > 0) {
				maxDistance--;
			}
		}else if (maxDistance < 100) {
			maxDistance++;
		}
		else {
			maxDistance = 100;
		}

	}


	

}

void EnemyEditorMode::updateGUI(const float& dt)
{
	selectorRect.setPosition(editorStateData.mousePosGrid->x * stateData->gridsize, editorStateData.mousePosGrid->y * stateData->gridsize);
	cursorText.setPosition(editorStateData.mousePosView->x + 100.f, editorStateData.mousePosView->y - 50.f);


	std::stringstream ss;
	ss <<
		"\n" << "EnemyCount: " <<amount
		<< "\n" << "Enemy Type: "<<type
		<< "\n" << "Time to spawn: " << TimeToSpawn
	<< "\n" << "Max Distance: " << maxDistance;
	cursorText.setString(ss.str());
}
void EnemyEditorMode::renderGUI(sf::RenderTarget& target)
{
	target.setView(*editorStateData.view);
	target.draw(selectorRect);
	target.draw(cursorText);
	target.setView(target.getDefaultView());
	target.draw(sidebar);
}

void EnemyEditorMode::initVariables()
{
	type = 0;
	amount = 1;
	TimeToSpawn = 20;
	maxDistance = 30;
}


void EnemyEditorMode::initGUI()
{
	//Text
	cursorText.setPosition(editorStateData.mousePosView->x, editorStateData.mousePosView->y - 50.f);
	cursorText.setFont(*editorStateData.font);
	cursorText.setCharacterSize(12);


	//General GUI
	selectorRect.setSize(sf::Vector2f{ stateData->gridsize, stateData->gridsize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
	selectorRect.setTexture(tMap->getileSheet());
	sidebar.setSize(sf::Vector2f{ (float)stateData->gfxSettings->resolution.width,80.f });
	sidebar.setPosition(0, stateData->gfxSettings->resolution.height - sidebar.getSize().y);
	sidebar.setFillColor(sf::Color{ 50,50,50,100 });
	sidebar.setOutlineThickness(1.f);
}
