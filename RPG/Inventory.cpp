#include "stdafx.h"
#include "Inventory.h"

void Inventory::initialize()
{
	itemCount = 0;
	itemArray = new Item* [maxCapacity];

	nullify();
}

void Inventory::freeMemory()
{
	for (size_t i = 0; i < itemCount; i++) {
		delete itemArray[i];
	}
	delete[] itemArray;
}


void Inventory::nullify(const unsigned from)
{
	for (size_t i = from; i < maxCapacity; i++) {
		itemArray[i] = nullptr;
	}
}

Inventory::Inventory(unsigned int capacity)
{
	maxCapacity = capacity;
	initialize();
}

Inventory::~Inventory()
{
	freeMemory();
}

const unsigned& Inventory::size() const
{
	return itemCount;
}

const unsigned& Inventory::maxSize() const
{
	return maxCapacity;
}

const bool Inventory::Empty() const
{
	return itemCount == 0;
}

const bool Inventory::add(Item* item)
{
	if (itemCount >= maxCapacity) {
		return false;
	}
	else {
		itemArray[itemCount++] = item->clone();
		return true;
	}
}

const bool Inventory::remove(const unsigned index)
{
	if (itemCount > 0 && index >0 && index < itemCount) {
		delete itemArray[index];
		itemArray[index] = nullptr;
		itemCount--;
		return true;
	}
	return false;
}

const bool Inventory::SavetoFile(const std::string fileName)
{
	return false;
}

const bool Inventory::loadromFile(const std::string fileName)
{
	return false;
}



void Inventory::clear()
{
	for (size_t i = 0; i < itemCount; i++) {
		delete itemArray[i];
	}
	itemCount = 0;
	nullify();
}
