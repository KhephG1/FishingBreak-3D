#include "stdafx.h"
#include "MovementComponent.h"
MovementComponent::MovementComponent(sf::Sprite& sprt, float maxV, float accel, float decel) : sprite{ sprt }, maxVel{ maxV }, acceleration{ accel }, deceleration{ decel } {
}
MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::getMaxVelocity() const
{
	return maxVel;
	// TODO: insert return statement here
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return velocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state) {
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0.f) {
			return true;
		}
		break;
	case MOVING:
		if (state!=IDLE) {
			return true;
		}
	case MOVING_RIGHT:
		if (velocity.x > 0) {
			return true;
		}
		break;
	case MOVING_LEFT:
		if (velocity.x < 0) {
			return true;
		}
		break;
	case MOVING_UP:
		if (velocity.y < 0) {
			return true;
		}
		break;
	case MOVING_DOWN:
		if (velocity.y > 0) {
			return true;
		}
		break;
	}

	return false;
}

void MovementComponent::move(const float dirX, const float dirY, const float dt)
{
	//acceleration for a sprite until it reaches max velocity

	velocity.x += acceleration * dirX;
	if (velocity.x > 0.f) {
		if (velocity.x > maxVel) {
			velocity.x = maxVel;
		}
	}
	else {
		if (velocity.x < -maxVel) {
			velocity.x = -maxVel;
		}
	}

	velocity.y += acceleration * dirY;
}


void MovementComponent::update(const float dt)
{
	//x direction accel / deceleration
	if (velocity.x > 0.f) {
		//max velocity check
		if (velocity.x > maxVel) {
			velocity.x = maxVel;
		}
		velocity.x -= deceleration;
		if (velocity.x < 0.f) {
			velocity.x = 0.f;
		}
	}
	else if (velocity.x < 0.f) {
		//max velocity check
		if (velocity.x < -maxVel) {
			velocity.x = -maxVel;
		}
		velocity.x += deceleration;
		if (velocity.x >0.f) {
			velocity.x = 0.f;
		}
	}
	//y direction accel / decel
	if (velocity.y > 0.f) {
		//max velocity check
		if (velocity.y > maxVel) {
			velocity.y = maxVel;
		}
		velocity.y -= deceleration;
		if (velocity.y < 0.f) {
			velocity.y = 0.f;
		}
	}
	else if (velocity.y < 0.f) {
		//max velocity check
		if (velocity.y < -maxVel) {
			velocity.y = -maxVel;
		}
		velocity.y += deceleration;
		if (velocity.y > 0.f) {
			velocity.y = 0.f;
		}
	}
	//final move
	sprite.move(velocity * dt);
}
