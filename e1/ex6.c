#include <stdio.h>

int main(int argc, char *argv[])
{
	int distance = 100;
	float power = 2.345f;
	double super_power = 54325.234523;
	char initial = 'A';
	char first_name[] = "Nameo!";
	char last_name[] = "naboo!";

	printf("you are %d miles away!\n", distance);
	printf("from learning your %f power!\n", power);
	printf("and gaining your %f super.\n", super_power);
	printf("I have have an %c in the class\n", initial);
	printf("I have the first name %s\n", first_name);
	printf("And the second name %s\n", last_name);
	printf("And am probably an idiot: %s %c, %s\n", first_name, initial, last_name);

	return 0;	
}