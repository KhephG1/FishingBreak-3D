#include "stdafx.h"
#include "Player.h"

//initializer functions
void Player::initVariables()
{
	initAttack = false;
	attacking = false;
	weapon->generate(3,1);
	damageTimerMax = 500;

}
void Player::initComponents()
{

}
void Player::initAnimations()
{
	animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 15.f, 12, 1, 15, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 15.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 15.f, 8, 1, 11, 1, 64, 64);
}
void Player::initInventory()
{
	weapon = new Sword{1, 20,"Resources/Images/Player/sword.png" };
	inventory = new Inventory{ 80 };
}
//constructors / destructors
Player::Player(float xpos, float ypos, sf::Texture* tex_sheet) {
	std::cout << "player constructor" << std::endl;
	initInventory();
	initSounds();
	createSprite(tex_sheet);
	sprite->setScale(1, 1);
	createMovementComponent(140.f, 700.f, 500.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite,10.f,5.f,44.f,54.f);
	createAttributeComponent(1);
	createSkillComponent();
	initAnimations();
	initVariables();
	setPosition(ypos, xpos);
}
Player::~Player()
{
	std::cout << "player destructor" << std::endl;
	delete weapon;
	delete inventory;
}

AttributeComponent* Player::getAttributeComponent()
{
	return attributeComponent;
}

void Player::updateAnimation(const float& dt)
{
	if (movementComp->getState(IDLE)) {
		animationComponent->play("IDLE",dt);

	}
	else if(movementComp->getState(MOVING_LEFT)) {
	
		sprite->setScale(1, 1);
		//the get "movementcomp->getvelocity..." arguments determine the speed at which the animation plays. If we are moving slower, the animation plays slower
		animationComponent->play("WALK_LEFT", dt,-movementComp->getVelocity().x, movementComp->getMaxVelocity());
		
	}
	else if (movementComp->getState(MOVING_RIGHT)) {
	
		sprite->setScale(1, 1);
		animationComponent->play("WALK_RIGHT", dt, movementComp->getVelocity().x, movementComp->getMaxVelocity());

	}
	else if (movementComp->getState(MOVING_UP)) {
		
		sprite->setScale(1, 1);
		animationComponent->play("WALK_UP", dt, -movementComp->getVelocity().y, movementComp->getMaxVelocity());
	
	}
	else if (movementComp->getState(MOVING_DOWN)) {
	
		sprite->setScale(1, 1);
		animationComponent->play("WALK_DOWN", dt, movementComp->getVelocity().y, movementComp->getMaxVelocity());

	}

}


void Player::update(const float& dt, sf::Vector2f mousePosView)
{
	updateSounds();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		attributeComponent->gainExp(20);
	movementComp->update(dt);

	updateAnimation(dt);
	hitbox->update();
	weapon->update(mousePosView, getCenter());

	
}

void Player::render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, sf::Vector2f light_position)
{
	//find the uniform hasTexture and set it to true
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target->draw(*sprite, shader);
		weapon->render(*target, shader);
	}
	else {
		target->draw(*sprite);
		weapon->render(*target);
	}
	
	if (show_hitbox) {
		hitbox->render(*target);
	}

}

void Player::loseHP(const int hp)
{
	attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	attributeComponent->gainHP(hp);
}

void Player::gainXP(const int xp)
{
	attributeComponent->gainExp(xp);
}

void Player::loseXP(const int xp)
{
	attributeComponent->loseXP(xp);
}

void Player::hideHitbox(const bool choice)
{
	if (choice == true) {
		show_hitbox = false;
	}
	else {
		show_hitbox = true;
	}
}

const bool Player::showHitbox() const
{
	return show_hitbox;
}

Weapon* Player::getWeapon() const 
{
	return weapon;
}

const std::string Player::CharacterTabString() const
{
	std::stringstream ss;
	if (this ) {
		ss << "Level: " << attributeComponent->level << std::endl;
		ss << "Experience: " << attributeComponent->exp << std::endl;
		ss << "Experience required: " << attributeComponent->expNext << std::endl;
		ss << "Weapon level: " << weapon->getLevel() << std::endl;
		ss << "Weapon type: " << weapon->getType() << std::endl;
		ss << "Weapon value: " << weapon->getValue() << std::endl;
		ss << "Weapon Range: " << weapon->getRange() << std::endl;
		
	}
	return ss.str();
}

const bool& Player::getInitAttack()
{
	return initAttack;
}

void Player::setinitAttack(const bool set)
{
	initAttack = set;
}

const bool Player::getDamageTimer()
{
	if(damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax) {
		damageTimer.restart();
		return true;
	}
	return false;
}

const unsigned Player::getDamage()
{
	return (rand() % ((attributeComponent->damageMax + weapon->getDamageMax()) - (attributeComponent->damageMin + weapon->getDamageMin()) + 1) + (attributeComponent->damageMin+ weapon->getDamageMin()))/10;
}

void Player::initSounds()
{

	if (!walkBuffer.loadFromFile("Resources/Sounds/walk.wav")) {
		std::cout << "ERROR::initSounds::walk" << std::endl;
	}
	if (!swingBuffer.loadFromFile("Resources/Sounds/swing.wav")) {
		std::cout << "ERROR::initSounds::swing" << std::endl;
	}

	walk.setBuffer(walkBuffer);
	swing.setBuffer(swingBuffer);
	
}

void Player::updateSounds()
{

}
