#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player: public Entity
{
private:
	bool attacking;
	void initVariables();
	void initComponents();
public:
	Player(float xpos, float ypos, sf::Texture* tex_sheet);
	virtual ~Player();
	virtual void update(const float dt);
};
#endif
