#include "../rt_scene.h"
#include "rd_read.h"

void	debug_rd_print_words(char *words[])
{
	while (*words)
	{
		printf("[%s] ", *words);
		words += 1;
	}
	printf("\n");
}
