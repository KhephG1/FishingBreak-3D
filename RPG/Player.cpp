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
	sprite->setScale(3, 3);
	createMovementComponent(300.f, 20.f, 3.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite,162,64,64,128);


	animationComponent->addAnimation("IDLE", 10.f, 2, 0, 3, 3, 128, 64);

	animationComponent->addAnimation("RUN", 11.f, 0, 0, 1, 3, 128, 64);

	animationComponent->addAnimation("JUMP", 20.f, 4, 0, 5, 3, 128, 64);

	animationComponent->addAnimation("ATTACK", 10.f, 0, 4, 6, 5, 128, 64);
}
Player::~Player()
{
}

void Player::update(const float dt)
{
	movementComp->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		attacking = true;
	} 
	if (attacking) {
		if (animationComponent->play("ATTACK", dt, true)) {
			attacking = false;
		}
	}
	if (movementComp->getState(IDLE)) {
		animationComponent->play("IDLE",dt);
	}
	else if(movementComp->getState(MOVING_LEFT)) {
		sprite->setOrigin(128, 0);
		sprite->setScale(-3, 3);
		animationComponent->play("RUN", dt,-movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_RIGHT)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(3, 3);
		animationComponent->play("RUN", dt, movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_UP)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(3, 3);
		animationComponent->play("RUN", dt, -movementComp->getVelocity().y, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_DOWN)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(3, 3);
		animationComponent->play("RUN", dt, movementComp->getVelocity().y, movementComp->getMaxVelocity());
	}

	hitbox->update();
}
