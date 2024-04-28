#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned level,unsigned value, std::string texture_file): Weapon{level,value, texture_file}
{
	
}

MeleeWeapon::~MeleeWeapon()
{
}

MeleeWeapon* MeleeWeapon::clone()
{
	return nullptr;
}

void MeleeWeapon::generate(const unsigned lvl_max, const unsigned lvl_min)
{
	level = rand() % (lvl_max - lvl_min + 1) + lvl_min;
	damageMin = pow(level * (2), 2);
	damageMax = pow(level * 3, 2);
	range = level * rand() % 100 + 500;
	value = level + damageMin + damageMax + range;
}

