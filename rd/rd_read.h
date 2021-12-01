#ifndef RT_READ_H
# define RT_READ_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "../vec3.h"
# include "../rt_scene.h"
# include "../libft/libft.h"

# define FT_BUFSIZ 4096
# define RD_EPSILON 1e-7

# define RD_ID_AMBIENT	"A"
# define RD_ID_CAMERA	"C"
# define RD_ID_LIGHT	"L"
# define RD_ID_SPHERE	"sp"
# define RD_ID_PLANE	"pl"
# define RD_ID_CYLINDER	"cy"

typedef enum e_element_type
{
	RD_ET_DUMMY,
	RD_ET_AMBIENT,
	RD_ET_CAMERA,
	RD_ET_LIGHT,
	RD_ET_SPHERE,
	RD_ET_PLANE,
	RD_ET_CYLINDER,
	RD_ET_UNEXPECTED,
}	t_element_type;

typedef struct s_plastic_buffer
{
	char	*body;
	size_t	cap;
	size_t	used;
}	t_plastic_buffer;

typedef union u_ull_double
{
	unsigned long long	ull;
	double				dbl;
}	t_ull_double;

typedef bool (*t_element_info_predicate)(const char*);

char	*rd_read_file_content(const char *filename);
void	debug_rd_print_words(char **words);

t_element_type	rd_detect_element_type(const char** words);

bool	rd_is_positive_real(const char *str);
bool	rd_is_ratio(const char *str);
bool	rd_is_fov_angle(const char *str);
bool	rd_is_vector(const char *str);
bool	rd_is_unit_vector(const char *str);
bool	rd_is_color_vector(const char *str);
void	rd_vectorize(const char* str, t_vec3* vector);


double	rd_str_to_double(const char *str);
bool	rd_is_finite(const double val);
double	rd_inf(bool positive);
double	rd_nan(void);

#endif
