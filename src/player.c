#include "entity.h"
#include "simple_logger.h"
#include "player.h"
#include "space.h"


extern Space *space;
extern int inputDir;
extern int attackDir;
extern int leftMouseInput;
extern int rightMouseInput;
int inputDir;
int attackDir;
 int leftMouseInput;
 int rightMouseInput;
Entity *newPlayer(Vec3D position,const char *name)
{
    Entity * ent;
    char buffer[255];
    int i;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/cube.obj");
    ent->texture = LoadSprite("models/cube_text.png",1024,1024);
	
	ent->type=PLAYER;
	ent->health=100;

	vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    ent->rotation.x = 90;
    sprintf(ent->name,"%s",name);
    ent->think = playerThink;
    ent->state = 0;
    //mgl_callback_set(&ent->body.touch,touch_callback,ent);
	ent->body.touch.data=ent;
	space_add_body(space,&ent->body);
    return ent;
}
void playerThink(Entity *self)
{
	float speed;
	speed=0.2;
	if(self->body.position.x<-3&&inputDir==-1){
		speed=0;
	}else if(self->body.position.x>3&&inputDir==1){
		speed=0;
	}
	if(inputDir!=0){
		attackDir=inputDir;
	}
	self->body.velocity.x=inputDir*speed;
	
}