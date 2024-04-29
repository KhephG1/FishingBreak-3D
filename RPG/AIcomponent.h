#pragma once
#include "Entity.h"
#include "AIFollow.h"
class AIcomponent
{
private:
	Entity& entity;
	Entity& self;
public:
	AIcomponent(Entity& entity, Entity& self);
	virtual ~AIcomponent();

};

