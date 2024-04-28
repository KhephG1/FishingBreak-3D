#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level,unsigned value, std::string texture_file): Weapon{level,value, texture_file}
{
	
}

RangedWeapon::~RangedWeapon()
{
}

RangedWeapon* RangedWeapon::clone()
{
	return nullptr;
}

void RangedWeapon::generate(const unsigned level_min, const unsigned level_max)
{
}
