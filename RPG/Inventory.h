#ifndef INVENTORY_H
#define INVENTORY_H
#include "Item.h"
class Inventory
{
private:
	//we will use an array of item pointers to track the items in our inventory
	Item** itemArray;
	unsigned itemCount;
	unsigned maxCapacity;
	//Private functions
	void initialize();
	void freeMemory();
	void nullify(const unsigned from = 0);
public:
	//Constructors and Destructors
	Inventory(unsigned int capacity);
	virtual ~Inventory();

	//Accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//modifiers
	//functions
	void clear();
	const bool Empty() const;
	const bool add(Item* item);
	const bool remove(const unsigned index);
	const bool SavetoFile(const std::string fileName);
	const bool loadromFile(const std::string fileName);
};

#endif