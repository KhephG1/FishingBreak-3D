#include "stdafx.h"
#include "DefaultMode.h"

DefaultMode::DefaultMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data) : EditorMode{ state_data,the_map,editor_state_data }
{
	initVariables();
	initGUI();
}

DefaultMode::~DefaultMode()
{
	delete texSelector;
}

void DefaultMode::update(const float& dt)
{
	updateInput(dt);
	updateGUI(dt);
}

void DefaultMode::render(sf::RenderTarget& target)
{
	renderGUI(target);
}

void DefaultMode::updateInput(const float& dt)
{
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorStateData.mousePosWindow)))
		{
			if (!texSelector->getActive())
			{
				if (this->tileAddLock == "FALSE")
				{
					if (this->tMap->hasTile(this->editorStateData.mousePosGrid->x, this->editorStateData.mousePosGrid->y, 0))
					{
						this->tMap->addTile(this->editorStateData.mousePosGrid->x, this->editorStateData.mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
					}
				}
				else
				{
					this->tMap->addTile(this->editorStateData.mousePosGrid->x, this->editorStateData.mousePosGrid->y, 0, this->textureRect, this->collision, this->type);
				}
			}
			else
			{
				this->textureRect = this->texSelector->getTextureRect();
			}
		}
	}
	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*editorStateData.mousePosWindow)))
		{
			if (!this->texSelector->getActive())
				tMap->removeTile(editorStateData.mousePosGrid->x, editorStateData.mousePosGrid->y, 0);
		}
	}

	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TOGGLE_COLLISION"))) && this->getKeyTime())
	{
		if (this->collision)
			this->collision = false;
		else
			this->collision = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TYPE_INC"))) && this->getKeyTime())
	{
		//CHANGE TO LIMIT TO MAX TYPE!!!!
		++this->type;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TYPE_DEC"))) && this->getKeyTime())
	{
		if (this->type > 0)
			--this->type;
	}

	//Set lock on / off
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(editorStateData.keybinds->at("TOGGLE_TILE_LOCK"))) && this->getKeyTime())
	{
		if (tileAddLock == "TRUE")
			this->tileAddLock = "FALSE";
		else
			tileAddLock = "TRUE";
	}
}



void DefaultMode::updateGUI(const float& dt)
{
	if (!texSelector->getActive()) {
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(editorStateData.mousePosGrid->x * stateData->gridsize, editorStateData.mousePosGrid->y * stateData->gridsize);
	}
	cursorText.setPosition(editorStateData.mousePosView->x + 100.f, editorStateData.mousePosView->y - 50.f);
	std::stringstream ss;
	ss << editorStateData.mousePosView->x << " " << editorStateData.mousePosView->y << "\n " << editorStateData.mousePosGrid->x << editorStateData.mousePosGrid->y
		<< "\n" << textureRect.left << " "
		<< textureRect.top << "\n" << "Collision: " << collision
		<< "\n" << "Type: " << type
		<< "\n" << "Tiles: " << tMap->getLayer(editorStateData.mousePosGrid->x, editorStateData.mousePosGrid->y, layer)
		<< "\n" << "Tile Lock: " << tileAddLock;
	cursorText.setString(ss.str());



	texSelector->update(sf::Vector2i{ (int)editorStateData.mousePosWindow->x, (int)editorStateData.mousePosWindow->y }, dt);
}

void DefaultMode::renderGUI(sf::RenderTarget& target)
{
	if (!texSelector->getActive()) {
		target.setView(*editorStateData.view);
		target.draw(selectorRect);
	}
	target.setView(stateData->window->getDefaultView());
	texSelector->render(target);
	target.draw(sidebar);
	target.setView(*editorStateData.view);
	target.draw(cursorText);
}

void DefaultMode::initVariables()
{
	textureRect = sf::IntRect{ 0,0,(int)stateData->gridsize, (int)stateData->gridsize };
	collision = false;
	type = DEFAULT;

	tileAddLock = "FALSE";
}

void DefaultMode::initGUI()
{
	cursorText.setPosition(editorStateData.mousePosView->x, editorStateData.mousePosView->y - 50.f);
	cursorText.setFont(*editorStateData.font);
	cursorText.setCharacterSize(12);
	cursorText.setString(std::to_string(editorStateData.mousePosView->x) + "," + std::to_string(editorStateData.mousePosView->y) + " " + std::to_string(textureRect.left));



	selectorRect.setSize(sf::Vector2f{ stateData->gridsize, stateData->gridsize });
	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
	selectorRect.setTexture(tMap->getileSheet());
	selectorRect.setTextureRect(textureRect);
	texSelector = new GUI::textureSelector{ 0,0,800.f,500.f,stateData->gridsize, tMap->getileSheet(), *editorStateData.font };
	sidebar.setSize(sf::Vector2f{ (float)stateData->gfxSettings->resolution.width,80.f });
	sidebar.setPosition(0, stateData->gfxSettings->resolution.height - sidebar.getSize().y);
	sidebar.setFillColor(sf::Color{ 50,50,50,100 });
	sidebar.setOutlineThickness(1.f);
	texSelector = new GUI::textureSelector{
		20.f, 20.f, 1000.f, 500.f,
		stateData->gridsize, this->tMap->getileSheet(),
		*editorStateData.font
	};
}
