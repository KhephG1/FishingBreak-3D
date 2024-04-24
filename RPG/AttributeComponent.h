#pragma once
class AttributeComponent
{
public:
	//Levelling
	unsigned level;
	//the current exp points of the player
	int exp;
	//the exp required for levelling up
	int expNext;
	int AttributePts;
	//Attributes
	int strength;
	int vitality;
	int agility;
	int intelligence;
	int dexterity;
	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defense;
	int luck;

	const bool dead();
	//constructors/ destructors
	AttributeComponent(int lvl);
	virtual~AttributeComponent();

	//Functions
	void updateStats(const bool reset);
	void updateLvl();
	void update();
	void gainExp(const unsigned ex);
	void gainHP(const int hp);
	void loseHP(const int hp);
	void loseXP(const int xp);
	std::string debugPrint()const;
};

