/** WARNING: This code is fresh and potentially isn't correct yet! */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "../dbg.h"

int read_string(char **out_string, int max_buffer)
{
	*out_string = calloc(1, max_buffer + 1);
	check_mem(*out_string);

	char *result = fgets(*out_string, max_buffer, stdin);
	check(result != NULL, "Input error.");

	return 0;

error:
	if(*out_string) free(*out_string);
	*out_string = NULL;
	return -1;
}