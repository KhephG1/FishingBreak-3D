#ifndef AI_H
#define AI_H
#include "Entity.h"
class AI
{
protected:
	Entity& self;
	Entity& entity;

public:
	AI(Entity& self, Entity& entity);
	virtual ~AI();
	virtual void update(const float& dt) = 0;

};

#endif