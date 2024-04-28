#pragma once
#include "AI.h"
class AIFollow :
    public AI
{
private:

public:
    AIFollow(Entity& self, Entity& entity);
    virtual ~AIFollow();
    void update(const float& dt);
};

