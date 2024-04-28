#ifndef ENTITY_H
#define ENTITY_H
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"
class Entity
{
private:
	void initVariables();

protected:
	AnimationComponent* animationComponent;
	sf::Texture* texture;
	//sf::Sprite* sprite;
	//sf::RectangleShape shape;
	MovementComponent* movementComp;
	HitboxComponent* hitbox;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;
	friend class GameState;
public:
	sf::Sprite* sprite;
	Entity();
	virtual ~Entity();
	//Component functions
	void createMovementComponent(const float maxSpeed, const float accel, const float decel);
	void createAnimationtComponent(sf::Texture& texture_sheet);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createAttributeComponent(const int lvl);
	void createSprite(sf::Texture* texture);
	void createSkillComponent();
	void createAIComponent();
	//Accessors
	virtual const sf::Vector2f getPosition() const;
	//returns the dimensions  (width and height) of the hitbox
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::Vector2i getGridPosition(const int GridSizeI) const;
	virtual const sf::FloatRect& getNextBounds(const float& dt) const;
	virtual const sf::Vector2f getCenter() const;
	
	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt,const float x, const float y);
	virtual void update(const float& dt, sf::Vector2f mousePosView) = 0;
	virtual void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox = false, sf::Vector2f light_position = sf::Vector2f{}) = 0;
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	//Calculations

	virtual const float getDistance(Entity* other) const;
};

#endif