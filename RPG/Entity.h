#ifndef ENTITY_H
#define ENTITY_H
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
class Entity
{
private:
	void initVariables();

protected:
	AnimationComponent* animationComponent;
	sf::Texture* texture;
	sf::Sprite* sprite;
	//sf::RectangleShape shape;
	MovementComponent* movementComp;
	HitboxComponent* hitbox;
	friend class GameState;
public:
	Entity();
	virtual ~Entity();
	//Component functions
	void createMovementComponent(const float maxSpeed, const float accel, const float decel);
	void createAnimationtComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createSprite(sf::Texture* texture);
	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt,const float x, const float y);
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif