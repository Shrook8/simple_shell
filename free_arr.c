#include "simple.h"


/**
 * custom_free_2d - free array
 * @arr_2D: arr
 *
 * Return: none
*/

void custom_free_2d(char **arr_2D)
{
	int a;

	for (a = 0; arr_2D[a] != NULL; a++)
		free(arr_2D[a]);
	free(arr_2D);
}
