#ifndef __PLAYER_H__
#define __PLAYER_H__
Entity *newPlayer(Vec3D position,const char *name);
void playerThink(Entity *self);
#endif