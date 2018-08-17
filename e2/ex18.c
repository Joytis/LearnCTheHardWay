#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* DIE :D */
void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

// A typedef creates a fake type, in this 
// case, for a function pointer!
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the 
 * compare_sb to do the sorting!
 */

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;

	// Allocates memory for bubble sort
	int *target = malloc(count * sizeof(int));

	// Checks for memory allocation error
	if(!target) die("Memory allocation error!");

	// Copies memory into new buffer. 
	memcpy(target, numbers, (count * sizeof(int)));

	for(i = 0; i < count; i++){
		for(j = 0; j < count - 1; j++){
			if(cmp(target[j], target[j+1]) > 0){
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b == 0){
		return 0;
	} else {
		return a % b;
	}
}

int dork_sort(int a, int b){
	return (a - b) - 3;
}

/**
 * Used to test that we are sorting thigns correctly
 * by doing the sord and printing it out
 */

void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if(!sorted) die("Memory Error!!");

	for(i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}

	printf("\n");

	// Do you have to free all pointers to given memory for
	// it to no loger deemed as "Accessible"
	free(sorted);

	// TEST BLOCK
	unsigned char *data = (unsigned char *)cmp;
	for(i = 0; i < 25; i++){
		printf("%02x:", data[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc < 2) die("USAGE: ex18 4 16 3 15 23 5 10 29");

	int i = 0;
	int count = argc - 1;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory Error!");

	for(i = 0; i < count; i++){
		numbers[i] = atoi(inputs[i]);
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	test_sorting(numbers, count, dork_sort);

	free(numbers);

	return 0;
}