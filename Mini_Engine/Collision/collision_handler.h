#ifndef COLLISION_HANDLER_H_INCLUDED
#define COLLISION_HANDLER_H_INCLUDED

#include "../Chunks/chunk.h"
#include "../Characters/character.h"

Collision getCollisionInfo(Chunk chunk[], Character character, EngineEvent event);

#endif // COLLISION_HANDLER_H_INCLUDED
