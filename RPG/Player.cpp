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
	createMovementComponent(100.f, 1500.f, 900.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite,10.f,5.f,44.f,54.f);
	createAttributeComponent(1);

	animationComponent->addAnimation("IDLE", 15.f, 0, 0,8, 0, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 15.f, 12, 1, 15, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT",15.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 15.f, 8, 1, 11, 1, 64, 64);
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
	/*
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
	*/
	if (movementComp->getState(IDLE)) {
		animationComponent->play("IDLE",dt);
	}
	else if(movementComp->getState(MOVING_LEFT)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		//the get "movementcomp->getvelocity..." arguments determine the speed at which the animation plays. If we are moving slower, the animation plays slower
		animationComponent->play("WALK_LEFT", dt,-movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_RIGHT)) {
		//sprite->setOrigin(258.f, 0);
		sprite->setScale(1, 1);
		animationComponent->play("WALK_RIGHT", dt, movementComp->getVelocity().x, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_UP)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		animationComponent->play("WALK_UP", dt, -movementComp->getVelocity().y, movementComp->getMaxVelocity());
	}
	else if (movementComp->getState(MOVING_DOWN)) {
		sprite->setOrigin(0, 0);
		sprite->setScale(1, 1);
		animationComponent->play("WALK_DOWN", dt, movementComp->getVelocity().y, movementComp->getMaxVelocity());
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

void Player::render(sf::RenderTarget* target, sf::Shader* shader)
{
	//find the uniform hasTexture and set it to true
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", getCenter());
		target->draw(*sprite, shader);
	}
	else {
		target->draw(*sprite);
	}
	
	if (show_hitbox) {
		hitbox->render(*target);
	}

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
