#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "entity.h"

Entity *newCube(Vec3D position,const char *name);
void touch_callback(void *data, void *context);
#endif