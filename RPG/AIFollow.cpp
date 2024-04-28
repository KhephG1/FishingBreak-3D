#include "stdafx.h"
#include "AIFollow.h"

AIFollow::AIFollow(Entity& self, Entity& entity):AI{self,entity}
{
}

AIFollow::~AIFollow()
{
}

void AIFollow::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec = entity.getPosition() - self.getPosition();
	float magnitude = std::sqrt(std::pow(moveVec.x, 2) + std::pow(moveVec.y, 2));

	moveVec.x /= magnitude;
	moveVec.y /= magnitude;

	if ((self.getPosition().x != entity.getPosition().x) && magnitude < 400.f) {
		self.move(dt,moveVec.x, moveVec.y);
	}
}
