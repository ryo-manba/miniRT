/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_read.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corvvs <corvvs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:35:57 by corvvs            #+#    #+#             */
/*   Updated: 2022/01/14 21:53:23 by corvvs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RD_READ_H
# define RD_READ_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "mr_vec3.h"
# include "libft.h"
# include "mr_read.h"

# define RD_UNIT_PREDICATE_EPSILON 1e-3

# define RD_ID_AMBIENT		"A"
# define RD_ID_CAMERA		"C"
# define RD_ID_LIGHT		"L"
# define RD_ID_SPHERE		"sp"
# define RD_ID_PLANE		"pl"
# define RD_ID_CYLINDER		"cy"
# define RD_ID_PARABOLOID	"pa"
# define RD_ID_CONE			"co"
# define RD_ID_SPOTLIGHT	"sl"
# define RD_ID_PYRAMIDLIGHT	"py"
# define RD_ID_TEXTURE		"tx"
# define RD_ID_CHECKER		"ch"
# define RD_ID_BUMPMAP		"bm"
# define RD_ID_MATERIAL		"ma"

typedef struct s_file_cursor
{
	size_t	line_number;
	char	*symbol;
	size_t	word_number;
}	t_file_cursor;

typedef struct s_temp_scene
{
	t_element		*ambient;
	t_element		*camera;
	t_element		*light_list;
	t_element		*object_list;
	t_element		*spotlight_list;
	t_file_cursor	cur;

	char			*content;
	char			**lines;
	char			**words;
	t_element		*el;
}	t_temp_scene;

typedef union u_ull_double
{
	unsigned long long	ull;
	double				dbl;
}	t_ull_double;

typedef bool	(*t_element_info_predicate)(t_file_cursor *, const char*);
typedef bool	(*t_element_info_extractor)(const char*, void*);

bool			rd_print_error(const char *error, t_temp_scene *temp_scene);
bool			rd_print_error_cur(t_file_cursor *cur, const char *error);
bool			rd_destroy_temp_scene_and_quit(t_temp_scene *temp_scene);
char			*rd_read_file_content(const char *filename);
void			debug_rd_print_words(char **words);
void			debug_rd_print_element(t_element *element);
void			debug_rd_print_element_list(t_element *element);
void			debug_rd_print_element_array(t_element **element);

t_element_type	rd_detect_element_type(t_temp_scene *scene, const char **words);

bool			rd_word_is_positive_real(t_file_cursor *cur, const char *str);
bool			rd_word_is_ratio(t_file_cursor *cur, const char *str);
bool			rd_word_is_fov_angle(t_file_cursor *cur, const char *str);
bool			rd_word_is_role_angle(t_file_cursor *cur, const char *str);

bool			rd_word_is_xpm_file_path(t_file_cursor *cur, const char *str);

bool			rd_word_is_vector(t_file_cursor *cur, const char *str);
bool			rd_word_is_unit_vector(t_file_cursor *cur, const char *str);
bool			rd_word_is_color_vector(t_file_cursor *cur, const char *str);

void			rd_vectorize(const char *str, t_vec3 *vector);
void			rd_free_strarray(char ***strs);

double			rd_str_to_double(const char *str);
bool			rd_is_finite(const double val);
double			rd_nan(void);

t_element		*rd_extract_element(t_element_type etype,
					const char **words);
void			rd_destroy_element(t_element *el);
void			**rd_get_element_slots(
					void **dest,
					t_element *el);
bool			rd_extract_double_scalar(const char *str, void *slot);
bool			rd_extract_double_vector(const char *str, void *slot);
bool			rd_extract_string(const char *str, void *slot);

void			rd_destroy_temp_scene_fail(t_temp_scene *temp_scene);
void			rd_destroy_temp_scene_succ(t_temp_scene *temp_scene);

void			rt_after_extraction(t_element *el);
bool			rd_attach_attribute(
					t_temp_scene *scene, t_element **list, t_element *el);
bool			rd_after_read(
					t_temp_scene *temp_scene, t_scene *scene);

void			debug_rd_print_vector(t_vec3 *vec);

#endif
