#include "enemy.h"
#include "entity.h"
#include "simple_logger.h"
#include "space.h"

extern Space *space;

Entity *newCube(Vec3D position,const char *name)
{
    Entity * ent;
    char buffer[255];
    int i;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    if (!ent)
    {
        return;
    }
    ent->objModel = obj_load("models/cube.obj");
    ent->texture = LoadSprite("models/cube_text.png",1024,1024);
	
	ent->type=BOX;

	vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    ent->rotation.x = 90;
    sprintf(ent->name,"%s",name);
    //ent->think = think;
    ent->state = 0;
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
	ent->body.touch.data=ent;
	space_add_body(space,&ent->body);
    return ent;
}
void touch_callback(void *data, void *context)
{
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data))
    {
        other = (Entity *)obody->touch.data;
		if(other->type==PLAYER){
			other->health-=10;
			entity_free(me);
			space_remove_body(space,me->body);
			slog("%s health is %i ",other->name,other->health);
		}
       // slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
}
