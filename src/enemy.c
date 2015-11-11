#include "enemy.h"
#include "entity.h"
#include "simple_logger.h"
#include "space.h"
#include "player.h"
extern Space *space;
extern int leftMouseInput;
extern int rightMouseInput;
extern int attackDir;
extern Entity* Player;
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
	ent->body.velocity.y=-.2;
	vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    ent->rotation.x = 90;
    sprintf(ent->name,"%s",name);
    ent->think = boxThink;
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
			
			space_remove_body(space,&me->body);
			entity_free(me);
			slog("%s health is %i ",other->name,other->health);
		}
       // slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
}

void boxThink(Entity *self){
	if(self->body.position.y<-4){
		space_remove_body(space,&self->body);
		entity_free(self);
	}
}

Entity *newSwordsmen(Vec3D position,const char *name)
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
	
	ent->type=SWORDSMEN;
	vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    ent->rotation.x = 90;
    sprintf(ent->name,"%s",name);
    ent->think = swordThink;
    ent->state = 0;
    mgl_callback_set(&ent->body.touch,sword_callback,ent);
	ent->body.touch.data=ent;
	space_add_body(space,&ent->body);
    return ent;
}

void swordThink(Entity *self){
	if(Player->body.position.x<self->body.position.x){
		self->body.position.x-=.1;
	}else{
		self->body.position.x+=.1;
	}
	//slog("%s SwordLoc is is %f ",self->name,self->body.position.x);
}
void sword_callback(void *data, void *context)
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
		
			
			if(((other->body.position.x<me->body.position.x)&&(leftMouseInput==1)&&(attackDir==1))||
				((other->body.position.x>me->body.position.x)&&(leftMouseInput==1)&&(attackDir==-1))){
				space_remove_body(space,&me->body);
				entity_free(me);
			}else{
				other->health-=20;
				if(other->body.position.x<me->body.position.x){
					me->body.position.x+=2;
				}else{
					me->body.position.x-=2;
				}
			}
			slog("left mouse input is %i ",leftMouseInput);
			slog("attackDir is %i ",attackDir);
		}else if(other->type==BOX){
			space_remove_body(space,&me->body);
			entity_free(me);
		}
       // slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
}
Entity *newFlying(Vec3D position,const char *name)
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
	
	ent->type=FLYING;
	vec3d_cpy(ent->body.position,position);
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    ent->rotation.x = 90;
    sprintf(ent->name,"%s",name);
    ent->think = flyingThink;
    ent->state = 0;
    mgl_callback_set(&ent->body.touch,flyingCallback,ent);
	ent->body.touch.data=ent;
	space_add_body(space,&ent->body);
    return ent;
}

void flyingThink(Entity *self){
	if(Player->body.position.x<self->body.position.x){
		self->body.position.x-=.1;
	}else{
		self->body.position.x+=.1;
	}
	//slog("%s SwordLoc is is %f ",self->name,self->body.position.x);
}
void flyingCallback(void *data, void *context)
{
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data))
    {
        other = (Entity *)obody->touch.data;
		if(other->type==BULLET){
		
			space_remove_body(space,&me->body);
			entity_free(me);
			slog("left mouse input is %i ",leftMouseInput);
			slog("attackDir is %i ",attackDir);
		}
       // slog("%s is ",other->name);
    }
    //slog("touching me.... touching youuuuuuuu");
}


