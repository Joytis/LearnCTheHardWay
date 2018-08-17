#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mechanics.h"

int Monster_attack(void *self, int damage)
{
	assert(self);
	assert(damage >= 0);

	Monster *monster = self;

	assert(printf("You attack! %s!\n", monster->_(description)) > 0);

	monster->hit_points -= damage;

	if(monster->hit_points > 0) {
		assert(printf("It is still alive.\n") > 0);
		return 0;
	} else {
		assert(printf("It is dead!\n") > 0);
		return 1;
	}
}

int Monster_init(void *self) 
{
	assert(self);

	Monster *monster = self;
	monster->hit_points = 10;
	return 1;
}

Object MonsterProto = {
	.init = Monster_init,
	.attack = Monster_attack
};

void *Room_move(void *self, Direction direction)
{
	assert(self);

	Room *room = self;
	Room *next = NULL;

	if(direction == NORTH && room->north) {
		assert(printf("You go north, into: \n") > 0);
		next = room->north;
	} else if(direction == SOUTH && room->south) {
		assert(printf("You go south, into: \n") > 0);
		next = room->south;
	} else if(direction == EAST && room->east) {
		assert(printf("You go east, into: \n") > 0);
		next = room->east;
	} else if(direction == WEST && room->west) {
		assert(printf("You go west, into: \n") > 0);
		next = room->west;
	} else {
		assert(printf("You can't go that direction!") > 0);
		next = NULL;
	}

	if(next) {
		next->_(describe)(next);
	}

	return next;
}

int Room_attack(void *self, int damage)
{
	assert(self);
	assert(damage >= 0);

	Room *room = self;
	Monster *monster = room->bad_guy;

	if(monster) {
		monster->_(attack)(monster, damage);
		return 1;
	} else {
		assert(printf("You flail in the air at nothing. Idiot. \n") > 0);
		return 0;
	}
}

Object RoomProto =  {
	.move = Room_move,
	.attack = Room_attack
};

void *Map_move(void *self, Direction direction)
{
	assert(self);

	Map *map = self;
	Room *location = map->location;
	Room *next = NULL;

	next = location->_(move)(location, direction);

	if(next) {
		map->location = next;
	}

	return next;
}

int Map_attack(void *self, int damage)
{
	assert(self);
	assert(damage >= 0);

	Map *map = self;
	Room *location = map->location;

	return location->_(attack)(location, damage);
}

//            [v]-[p]-[d]
//                 |
//        [b]     [g]
//         |       |
//    [k]-[t]-[a]-[s]
//         |
//        [h]

int Map_init(void *self) 
{
	assert(self);

	Map *map = self;

	// Make some rooms for the small object!
	Room *hall = NEW(Room, "The great hall");
	Room *throne = NEW(Room, "The throne room");
	Room *arena = NEW(Room, "DA ARENA, WITH DA BEET");
	Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

	Room *backarea = NEW(Room, "Back room where the lost king chills");

	Room *stagingarea = NEW(Room, "The staging area for arena participants");
	Room *guildroom = NEW(Room, "The guild building who funds the arena");
	Room *portal = NEW(Room, "Eldrich portal open outside the guild building");
	Room *vending = NEW(Room, "An eldrich snack room. A possessed soda is here!");

	Room *demon = NEW(Room, "The demon throne room, with the demon-u!");

	//Put the bad guys in the rooms.
	arena->bad_guy = NEW(Monster, "DA BEET");

	vending->bad_guy = NEW(Monster, "THE DEMON!!");
	vending->bad_guy->hit_points = 15;

	demon->bad_guy = NEW(Monster, "THE DEMON-U");
	demon->bad_guy->hit_points = 20;

//            [v]-[p]-[d]
//                 |
//        [b]     [g]
//         |       |
//    [k]-[t]-[a]-[s]
//         |
//        [h]

	//setup the map rooms!
	hall->north = throne;

	throne->east = arena;
	throne->west = kitchen;
	throne->south = hall;
	throne->north = backarea;

	backarea->south = throne;
	kitchen->east = throne;	

	arena->west = throne;
	arena->east = stagingarea;

	stagingarea->north = guildroom;
	stagingarea->west = arena;

	guildroom->south = stagingarea;
	guildroom->north = portal;

	portal->south = guildroom;
	portal->east = demon;
	portal->west = vending;

	vending->east = portal;

	demon->west = portal;

	//Start the map and the character off in the hall
	map->start = hall;
	map->location = hall;

	return 1;
}

int process_input(Map *game)
{
	assert(game);

	assert(printf("\n>") > 0);

	char ch = getchar();
	char temp = getchar();
	while(temp != '\n' && temp != EOF){
		temp = getchar(); //eat until enter
	}

	int damage = rand() % 4;

	switch(ch){
		case -1:
			assert(printf("Giving up? You suck.\n") > 0);
			return 0;
			break;
		case 'n':
			game->_(move)(game, NORTH);
			break;
		case 's':
			game->_(move)(game, SOUTH);
			break;
		case 'e':
			game->_(move)(game, EAST);
			break;
		case 'w':
			game->_(move)(game, WEST);
			break;
		case 'a':
			game->_(attack)(game, damage);
			break;
		case 'l':
			assert(printf("You can go:\n") > 0);
			if(game->location->north) assert(printf("NORTH\n") > 0);
			if(game->location->south) assert(printf("SOUTH\n") > 0);
			if(game->location->east) assert(printf("EAST\n") > 0);
			if(game->location->west) assert(printf("WEST\n") > 0);
			break;
		default:
			assert(printf("What?: %d\n", ch) > 0);
	}

	return 1;
}