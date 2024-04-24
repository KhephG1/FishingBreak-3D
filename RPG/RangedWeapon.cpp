#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned value, std::string texture_file): Weapon{value, texture_file}
{
	
}

RangedWeapon::~RangedWeapon()
{
}

RangedWeapon* RangedWeapon::clone()
{
	return nullptr;
}
