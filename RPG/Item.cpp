#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

Item::Item(unsigned value)
{
	initVariables();
	this->value = value;
	type = DEFAULT_ITEM;
}

Item::~Item()
{
}

