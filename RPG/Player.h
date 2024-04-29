#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Items.h"
#include "Inventory.h"
class Player: public Entity
{
private:
	bool facing_right;
	bool attacking;
	bool show_hitbox;
	Weapon* weapon;
	bool initAttack;
	Inventory* inventory;
	void initVariables();
	void initComponents();
	void initAnimations();
	void initInventory();
	sf::Int32 damageTimerMax;
	sf::Clock damageTimer;
	sf::SoundBuffer walkBuffer;
	sf::Sound walk;
	sf::SoundBuffer swingBuffer;
	sf::Sound swing;
public:
	bool dead{ false };
	Player(float xpos, float ypos, sf::Texture* tex_sheet);
	virtual ~Player();
	AttributeComponent* getAttributeComponent();
	//Functions
	
	void updateAnimation(const float& dt);
	virtual void update(const float& dt, sf::Vector2f mousePosView) override;
	virtual void render(sf::RenderTarget* target, sf::Shader* shader, const bool show_hitbox = false, sf::Vector2f light_position = sf::Vector2f{}) override;
	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainXP(const int xp);
	void loseXP(const int xp);
	void hideHitbox(const bool choice);
	const bool showHitbox() const;
	 Weapon* getWeapon()const;
	 const std::string CharacterTabString()const;
	 const bool& getInitAttack();
	 void setinitAttack(const bool set);
	 const bool getDamageTimer();
	 const unsigned getDamage();
	 void initSounds();
	 void updateSounds();
};
#endif
