#include <stdio.h>
#include <stdlib.h>
#include "../dbg.h"

typedef enum {
	THIS, IS, A, COOL, ENUM
} Cool;

int main(int argc, char *argv[])
{
	//This program is to test ALL c operators! :D
	int int_a; // Creates memory for 32bit integer on stack! 
	unsigned int int_b; // Creates memory for a 32 bit integer on the stack, unsigned. 
	signed int int_c; //Same thing as int_a
	long int int_d; // Double the storage! 64 bits!
	short int int_e; // Half the storage! 16 bits!
	const int int_f = 100; //Const. Won't be changed after init

	double doub_b;
	float flo_c;
	char char_d;
	void *e = malloc(sizeof(int));
	int *f = e;

	check_mem(e);

	
	

error:
	if(e) free(e);
	if(f) free(f);


}