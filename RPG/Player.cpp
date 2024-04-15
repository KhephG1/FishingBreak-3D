#include "stdafx.h"
#include "Player.h"
//initializer functions
void Player::initVariables()
{
	attacking = false;
}
void Player::initComponents()
{

}
//constructors / destructors
Player::Player(float xpos, float ypos, sf::Texture* tex_sheet) {
	initVariables();
	createSprite(tex_sheet);
	setPosition(xpos, ypos);
	sprite->setScale(1, 1);
	createMovementComponent(100.f, 1500.f, 500.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite,86.f,66.f,86.f,111.f);
	createAttributeComponent(1);

	animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);

	animationComponent->addAnimation("RUN", 6.f, 0, 1, 11, 1, 192, 192);


	animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}
Player::~Player()
{
}

AttributeComponent* Player::getAttributeComponent()
{
	return attributeComponent;
}

void Player::updateAnimation(const float& dt)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		attacking = true;
	} 
	if (attacking) {
		stopVelocity();
		if (sprite->getScale().x > 0.f) {//facing left
			sprite->setOrigin(96.f, 0.f);
		}
		else {//facing right
			sprite->setOrigin(258.f + 96.f, 0.f);
		}
		if (animationComponent->play("ATTACK", dt, true)) {
			sprite->setOrigin(258.f, 0.f);
			attacking = false;
			if (sprite->getScale().x > 0.f) {//facing left
				sprite->setOrigin(0.f, 0.f);
			}
			else {//facing right
				sprite->setOrigin(258.f, 0.f);
			}
		}
	}
	if (movementComp->getState(IDLE)) {
		animationComponent->play("IDLE",dt);
	}
	else if(movementComp->getState(MOVING_LEFT)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		animationComponent->play("RUN", dt,-movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_RIGHT)) {
		sprite->setOrigin(258.f, 0);
		sprite->setScale(-1, 1);
		animationComponent->play("RUN", dt, movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_UP)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		animationComponent->play("RUN", dt, -movementComp->getVelocity().y, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_DOWN)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		animationComponent->play("RUN", dt, movementComp->getVelocity().y, movementComp->getMaxVelocity());
	}

}

void Player::updateAttack()
{
}


void Player::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		attributeComponent->gainExp(20);
	movementComp->update(dt);
	updateAttack();
	updateAnimation(dt);
	hitbox->update();
	
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*sprite);
	hitbox->render(*target);

}

void Player::loseHP(const int hp)
{
	attributeComponent->hp -= hp;
	if (attributeComponent->hp < 0) {
		attributeComponent->hp = 0;
	}
}

void Player::gainHP(const int hp)
{
	attributeComponent->hp += hp;
	if (attributeComponent->hp > attributeComponent->hpMax) {
		attributeComponent->hp = attributeComponent->hpMax;
	}
}

void Player::gainXP(const int xp)
{
	attributeComponent->gainExp(xp);
}

void Player::loseXP(const int xp)
{
	attributeComponent->exp -= xp;
	if (attributeComponent->exp < 0) {
		attributeComponent->exp = 0;
	}
}
