#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	struct Intabro e = {.a = 2, .b = 3};

	puts("%d %d", struct Intabro.a, struct Intabro.b);

	puts("hello world");

	puts(" Hey bro, I'm this cool guy \r");
	puts(" Learning about cpp! \r\n");
	puts(" I'd appreciate it if you were also cool\r\n");
	puts(" Not only because you're cool, but because I'm coll too!");

	return 0;

}