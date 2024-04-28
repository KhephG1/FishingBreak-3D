#include "stdafx.h"
#include "AI.h"

AI::AI(Entity& self, Entity& entity) : self{ self }, entity{ entity } {}
AI::~AI() {}