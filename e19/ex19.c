#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mechanics.h"


Object MapProto = {
	.init = Map_init,
	.move = Map_move,
	.attack = Map_attack
};


//           []-[]-[]
//               |
//        []    []
//         |     |
//     []-[]-[]-[]
//         |
//        []


int main(int argc, char *argv[])
{
	assert(argc >= 0);
	assert(argv);

	// simple way to set up randomness
	srand(time(NULL));

	// make our map to work with.
	Map *game = NEW(Map, "The Hall of the Minotaur!");

	assert(printf("You enter the: ") > 0);
	
	game->location->_(describe)(game->location);

	while(process_input(game)){

	}
	return 0;
}















