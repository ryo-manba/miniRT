#include "rd_read.h"

int main(int argc, char **argv)
{
	char	*content;
	char	**lines;

	content = rd_read_file_content("test.rt");
	if (!content)
	{
		printf("Error\n");
		return (1);
	}

	lines = ft_split(content, '\n');
	if (!lines)
	{
		printf("Error\n");
		return (1);
	}
	size_t	i;
	char **words;
	i = 0;
	while (lines[i])
	{
		printf("%s\n", lines[i]);
		words = ft_split(lines[i], ' ');
		debug_rd_print_words(words);
		t_element_type etype = rd_detect_element_type((const char**)words);
		printf("%d\n", etype);
		i += 1;
	}

	(void)argc;
	printf("%d\n", rd_is_vector(argv[1]));
	printf("%d\n", rd_is_unit_vector(argv[1]));
	printf("%d\n", rd_is_color_vector(argv[1]));
}
