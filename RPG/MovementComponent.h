#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H


enum movement_states {IDLE = 0,MOVING, MOVING_LEFT,MOVING_RIGHT,MOVING_DOWN,MOVING_UP};
class MovementComponent
{
public:
	sf::Sprite& sprite;
	float maxVel;
	sf::Vector2f velocity;
	float acceleration;
	float deceleration;

public:

	MovementComponent(sf::Sprite& sprt, float maxS, float acccel, float decel);
	virtual ~MovementComponent();
	//Accessors
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;
	const bool getState(const short unsigned state) const;
	//functions
	void move(const float dirX, const float dirY, const float dt);
	void update(const float dt);
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();
};
#endif
