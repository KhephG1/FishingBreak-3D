#ifndef ITEM_H
#define ITEM_H

enum ItemTypes{DEFAULT_ITEM = 0, RANGEDWEAPON, MELEEWEAPON};
enum ItemRarities { COMMON = 0, UNCOMMON,RARE,EPIC,LENGENDARY,MYTHIC,NUTSINSANEBONKERSRARITY};
class Item
{
private:
	void initVariables();
protected:
	//Variables
	unsigned value;
	short unsigned type;
	unsigned level;

public:
	Item(unsigned value, unsigned level);
	virtual ~Item();


	//Functions
	virtual Item* clone() = 0;
	//Accessors
	const short unsigned& getType() const { return type; }
	const short unsigned& getLevel() const { return level; }
	const short unsigned& getValue() const { return value; }
};

#endif