#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	skills.push_back(Skill{HEALTH});
	skills.push_back(Skill{ ATTACK});
	skills.push_back(Skill{ ACCURACY});
	skills.push_back(Skill{ ENDURANCE});
}

SkillComponent::~SkillComponent()
{
}

int SkillComponent::getSkill(const int skill)
{
	if (skill < 0 || skill >= skills.size()) {
		throw std::out_of_range{ "index out of range of skill vector" };
	}else{
		return skills.at(skill).getLevel();

	}
}

const void SkillComponent::gainExp(const int skill, const int amount)
{
	if (skill < 0 || skill >= skills.size()) {
		throw std::out_of_range{ "index out of range of skill vector" };
	}
	else {
		skills.at(skill).gainExp(amount);
	}
}
