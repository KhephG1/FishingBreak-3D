#include "stdafx.h"
#include "Enemy.h"


Enemy::~Enemy()
{
}


void Enemy::initVariables()
{

}

void Enemy::initAnimations()
{
	animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	animationComponent->addAnimation("WALK_DOWN", 15.f, 0, 1, 3, 1, 64, 64);
	animationComponent->addAnimation("WALK_UP", 15.f, 12, 1, 15, 1, 64, 64);
	animationComponent->addAnimation("WALK_LEFT", 15.f, 4, 1, 7, 1, 64, 64);
	animationComponent->addAnimation("WALK_RIGHT", 15.f, 8, 1, 11, 1, 64, 64);
}
//constructors / destructors
Enemy::Enemy(EnemySpawner& enemy_Spawner, float xpos, float ypos, sf::Texture* tex_sheet) :spawner{ enemy_Spawner } {
	initVariables();
	createSprite(tex_sheet);
	sprite->setScale(1, 1);
	createMovementComponent(100.f, 1500.f, 900.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite, 10.f, 5.f, 44.f, 54.f);
	initAnimations();
	setPosition(ypos, xpos);
}

void Enemy::updateAnimation(const float& dt)
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

void Enemy::update(const float& dt, sf::Vector2f mousePosView)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		attributeComponent->gainExp(20);
	movementComp->update(dt);
	//updateAttack();
	updateAnimation(dt);
	hitbox->update();
	

}

void Enemy::render(sf::RenderTarget* target, sf::Shader* shader)
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

	
	hitbox->render(*target);
}

