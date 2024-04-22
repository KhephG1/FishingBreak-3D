#include "stdafx.h"
#include "Rat.h"

Rat::Rat(float xpos, float ypos, sf::Texture* tex_sheet): Enemy{}
{
	initVariables();
	createSprite(tex_sheet);
	sprite->setScale(1, 1);
	createMovementComponent(100.f, 1500.f, 900.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite, 10.f, 5.f, 44.f, 54.f);
	initAnimations();
	setPosition(ypos, xpos);
}

Rat::~Rat()
{
}

void Rat::initVariables()
{

}

void Rat::initAnimations()
{
	animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 3, 3, 3, 60, 64);
	animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 2, 3, 2, 60, 64);
	animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);

}


void  Rat::updateAnimation(const float& dt)
{
	if (movementComp->getState(IDLE)) {
		animationComponent->play("IDLE", dt);
	}
	else if (movementComp->getState(MOVING_LEFT)) {

		sprite->setScale(1, 1);
		//the get "movementcomp->getvelocity..." arguments determine the speed at which the animation plays. If we are moving slower, the animation plays slower
		animationComponent->play("WALK_LEFT", dt, -movementComp->getVelocity().x, movementComp->getMaxVelocity());
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

void  Rat::update(const float& dt, sf::Vector2f mousePosView)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		attributeComponent->gainExp(20);
	movementComp->update(dt);
	//updateAttack();
	updateAnimation(dt);
	hitbox->update();


}

void  Rat::render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position)
{
	//find the uniform hasTexture and set it to true
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target->draw(*sprite, shader);

	}
	else {
		target->draw(*sprite);

	}


	hitbox->render(*target);
}
