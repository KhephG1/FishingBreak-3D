#include "stdafx.h"
#include "GUI.h"
using namespace GUI;
Button::Button(float x, float y, float width, float height, std::string text, sf::Font* font,
	sf::Color Outline_idle, sf::Color Outline_hover, sf::Color Outline_active,
	sf::Color text_idle, sf::Color text_hover, sf::Color text_active,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id){
	buttonState = BTN_IDLE;
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(x, y));
	this->id = id;
	this->font = font;
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(Outline_idle);
	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setFillColor(text_idle);
	this->text.setCharacterSize(character_size);
	this->text_idle = text_idle;
	this->text_hover = text_hover;
	this->text_active = text_active;
	this->text.setPosition(shape.getPosition().x + ((shape.getGlobalBounds().width - this->text.getGlobalBounds().width) /2.0f), shape.getPosition().y + ((shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.0f));
	this->idlecolour = idleColor;
	this->hovercolour = hoverColor;
	this->activecolour = activeColor;
	Outlineidlecolour = Outline_idle;
	Outlinehovercolour = Outline_hover;
	Outlineactivecolour = Outline_active;
}

Button::~Button()
{
}

const bool Button::isPressed() {
	if (buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}

const short unsigned& GUI::Button::getID() const
{
	return id;
}

const std::string GUI::Button::getText() const
{
	return text.getString();
}

void GUI::Button::setText(const std::string txt)
{
	text.setString(txt);
}

void GUI::Button::setID(const short unsigned eyedee)
{
	id = eyedee;
}

void Button::update(sf::Vector2f& mousePos)
{
	/*update the booleans for hover and pressed*/
	buttonState = BTN_IDLE;
	if (shape.getGlobalBounds().contains(mousePos)) {
		buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = BTN_PRESSED;
		}
	}

	switch (buttonState) {
	case BTN_IDLE:
		shape.setFillColor(idlecolour);
		text.setFillColor(text_idle);
		shape.setOutlineColor(Outlineidlecolour);
		break;
	case BTN_HOVER:
		shape.setFillColor(hovercolour);
		text.setFillColor(text_hover);
		shape.setOutlineColor(Outlinehovercolour);
		break;
	case BTN_PRESSED:
		shape.setFillColor(activecolour);
		text.setFillColor(Outlinehovercolour);
		shape.setOutlineColor(Outlineactivecolour);
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}
	
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}

DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& fnt, std::vector<std::string> a_list, unsigned default_idx) : font{ fnt }, show_list{ false }, keyTimeMax{ 3.f },keyTime { keyTimeMax }
{
	unsigned counter{};
	for (auto str : a_list) {
		list.push_back(new Button{ x, y + (counter + 1) * height, width,height, str, &font,
		 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent,(unsigned short)counter });

		counter++;
	}
	activeElement = new Button{ x, y, width, height,a_list.at(default_idx), &font, 
		 sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color::White, sf::Color{100,100,100}, sf::Color::Blue, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent };
}

GUI::DropDownList::~DropDownList()
{
	delete activeElement;
	for (auto& i : list) {
		delete i;
	}
}

const bool GUI::DropDownList::getkeyTime()
{
	if (keyTime >= keyTimeMax) {
		keyTime = 0.f;
		return true;
	}
	return false;
}

void GUI::DropDownList::updateKeyTime(const float& dt)
{

	if (keyTime < keyTimeMax) {
		keyTime += 10.f * dt;
	}
}

const unsigned short GUI::DropDownList::getlistID()
{
	return activeElement->getID();
}

void GUI::DropDownList::update(sf::Vector2f& mousePos, const float& dt)
{
	updateKeyTime(dt);
	if (show_list) {
		for (auto& i : list) {
			i->update(mousePos);
			if (i->isPressed() && getkeyTime()) {
				show_list = false;
				activeElement->setText(i->getText());
				activeElement->setID(i->getID());
			}
		}
	}
	activeElement->update(mousePos);

	if (activeElement->isPressed() && getkeyTime()) {
		show_list = !show_list;
	}
}

void GUI::DropDownList::render(sf::RenderTarget* target)
{
	activeElement->render(target);
	if (show_list) {
		for (auto& i : list) {
			i->render(target);
		}
	}
}


//TEXTURE SELECTOR_______________________-

GUI::textureSelector::textureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texSheet)
{
	GridSize = gridSize;
	bounds.setSize(sf::Vector2f{ width, height });
	bounds.setFillColor(sf::Color{ 50,50,50,100 });
	bounds.setPosition(x, y);
	bounds.setOutlineColor(sf::Color{ 255,255,255,200 });
	bounds.setOutlineThickness(1.5);
	sheet.setTexture(*texSheet);
	sheet.setPosition(x, y);
	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width) {
		sheet.setTextureRect(sf::IntRect{ 0,0,(int)bounds.getGlobalBounds().width, (int)sheet.getGlobalBounds().height });
	}
	if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height) {
		sheet.setTextureRect(sf::IntRect{ 0,0,(int)sheet.getGlobalBounds().width, (int)bounds.getGlobalBounds().height });
	}
	selector.setPosition(x, y);
	selector.setSize(sf::Vector2f{ gridSize,gridSize });
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineColor(sf::Color::Red);
	selector.setOutlineThickness(1.5f);
	active = false;
}

GUI::textureSelector::~textureSelector()
{
}

const bool& GUI::textureSelector::getActive() const
{
	return active;
}

void GUI::textureSelector::update(const sf::Vector2i& mousePosWindow)
{
	if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
		active = true;
	}
	else {
		active = false;
	}
	if (active) {
		mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<unsigned>(GridSize);
		mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<unsigned>(GridSize);
	}
	selector.setPosition(bounds.getPosition().x + mousePosGrid.x * GridSize, bounds.getPosition().y + mousePosGrid.y * GridSize);
}

void GUI::textureSelector::render(sf::RenderTarget& target)
{
	target.draw(bounds);
	target.draw(sheet);
	target.draw(selector);
}
