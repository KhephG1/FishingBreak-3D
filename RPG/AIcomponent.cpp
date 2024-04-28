#include "stdafx.h"
#include "AIcomponent.h"

AIcomponent::AIcomponent(Entity& entity, Entity& self): entity{entity}, self {self}
{
}

AIcomponent::~AIcomponent()
{
}
