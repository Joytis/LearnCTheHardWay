#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

void Object_destoy(void *self)
{
	assert(self);

	Object *obj = self;

	if(obj){
		if(obj->description) free(obj->description);
		free(obj);
	}
}

void Object_describe(void *self)
{
	assert(self);

	Object *obj = self;
	assert(printf("%s.\n", obj->description) > 0);
}

int Object_init(void *self)
{
	assert(self);
	// do nothing, really. 
	return 1;
}

void *Object_move(void *self, Direction direction)
{
	assert(self);

	assert(printf("You can't go in that direction.\n") > 0);
	return NULL;
}

int Object_attack(void *self, int damage)
{
	assert(self);
	assert(damage >= 0);

	assert(printf("You can't attack that.\n") > 0);
	return 0;
}

void *Object_new(size_t size, Object proto, char *description)
{
	assert(size);
	assert(sizeof(proto) <= size);
	assert(description);

	// setup the default functions in case they aren't set yet. 
	if(!proto.init) proto.init = Object_init;
	if(!proto.describe) proto.describe = Object_describe;
	if(!proto.destroy) proto.destroy = Object_destoy;
	if(!proto.attack) proto.attack = Object_attack;
	if(!proto.move) proto.move = Object_move;

	// This seems weird, but we can make a struct of one size,
	// then point a different pointer at it to "cast" it.
	Object *el = calloc(1, size);
	assert(el != NULL);

	*el = proto;

	// copy the description over
	el->description = strdup(description);
	assert(el->description != NULL);

	// initiailze it with whatever init we were given!
	if(!el->init(el)) {
		// Looks like it didn't initialize properly!
		el->destroy(el);
		return NULL;
	} else {
		//all done. We made an object of any type!
		return el;
	}
}
















