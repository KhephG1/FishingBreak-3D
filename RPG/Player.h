#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
class Player: public Entity
{
private:
	bool facing_right;
	bool attacking;
	bool show_hitbox;
	void initVariables();
	void initComponents();
public:
	Player(float xpos, float ypos, sf::Texture* tex_sheet);
	virtual ~Player();
	AttributeComponent* getAttributeComponent();
	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target) override;
	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainXP(const int xp);
	void loseXP(const int xp);
	void hideHitbox(const bool choice);
	const bool showHitbox() const;
};
#endif
