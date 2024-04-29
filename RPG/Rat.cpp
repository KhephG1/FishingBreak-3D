#include "stdafx.h"
#include "Rat.h"

Rat::Rat(float xpos, float ypos, sf::Texture* tex_sheet,EnemySpawnerTile& spawnerTile, Entity& plyr): Enemy{spawnerTile}
{
	initVariables();
	
	createSprite(tex_sheet);
	sprite->setScale(1, 1);
	createMovementComponent(20.f, 400.f, 200.f);
	createAnimationtComponent(*tex_sheet);
	createHitboxComponent(*sprite, 10.f,15.f, 44.f, 44.f);
	createAttributeComponent(1);
	generateAttributes(attributeComponent->level);
	initAnimations();
	setPosition(ypos, xpos);
	initGUI();

	follow = new AIFollow{ *this,plyr };
}

Rat::~Rat()
{
	delete follow;
}

void Rat::initVariables()
{
	
}

void Rat::initAnimations()
{
	animationComponent->addAnimation("IDLE", 12.f, 0, 0, 3, 0, 60, 64);
	animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 3, 3, 3, 60, 64);
	animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);

}

void Rat::initGUI()
{
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setSize(sf::Vector2f{ 50.f,10.f });
	hpBar.setPosition(sprite->getPosition());
}

void Rat::initAI()
{
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
	if (damageTimer.getElapsedTime().asMilliseconds() <= damageTimerMax) {
		sprite->setColor(sf::Color::Red);
	}
	else {
		sprite->setColor(sf::Color::White);
	}
}

void  Rat::update(const float& dt, sf::Vector2f mousePosView)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		attributeComponent->gainExp(20);
	movementComp->update(dt);
	hpBar.setSize(sf::Vector2f{ 50.f * ((float)attributeComponent->hp / attributeComponent->hpMax),10.f });
	hpBar.setPosition(sprite->getPosition());
	//updateAttack();
	updateAnimation(dt);
	hitbox->update();
	follow->update(dt);

}

void  Rat::render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox, const sf::Vector2f light_position)
{
	//find the uniform hasTexture and set it to true
	if (shader) {
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target->draw(*sprite, shader);
		target->draw(hpBar);

	}
	else {
		target->draw(*sprite);
		target->draw(hpBar);
	}


	//hitbox->render(*target);
}
