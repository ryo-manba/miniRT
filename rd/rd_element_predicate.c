#include "rd_read.h"

static const t_element_info_predicate	ambient_predicates[] = {
	rd_is_ratio,
	rd_is_color_vector,
	NULL,
};

static const t_element_info_predicate	camera_predicates[] = {
	rd_is_vector,
	rd_is_unit_vector,
	rd_is_fov_angle,
	NULL,
};

static const t_element_info_predicate	light_predicates[] = {
	rd_is_vector,
	rd_is_ratio,
	rd_is_color_vector,
	NULL,
};

static const t_element_info_predicate	sphere_predicates[] = {
	rd_is_vector,
	rd_is_positive_real,
	rd_is_color_vector,
	NULL,
};

static const t_element_info_predicate	plane_predicates[] = {
	rd_is_vector,
	rd_is_unit_vector,
	rd_is_color_vector,
	NULL,
};

static const t_element_info_predicate	cylinder_predicates[] = {
	rd_is_vector,
	rd_is_unit_vector,
	rd_is_positive_real,
	rd_is_positive_real,
	rd_is_color_vector,
	NULL,
};

static bool	line_matches_predicates(
	const char** words,
	const t_element_info_predicate* predicates)
{
	size_t	i;

	i = 0;
	while (words[i + 1])
	{
		if (!(predicates[i])(words[i + 1]))
		{
			return (false);
		}
		i += 1;
	}
	return (true);
}

t_element_type	rd_detect_element_type(const char** words)
{
	if (ft_strcmp(words[0], RD_ID_AMBIENT) == 0 &&
		line_matches_predicates(words, ambient_predicates))
		return (RD_ET_AMBIENT);
	if (ft_strcmp(words[0], RD_ID_CAMERA) == 0 &&
		line_matches_predicates(words, camera_predicates))
		return (RD_ET_CAMERA);
	if (ft_strcmp(words[0], RD_ID_LIGHT) == 0 &&
		line_matches_predicates(words, light_predicates))
		return (RD_ET_LIGHT);
	if (ft_strcmp(words[0], RD_ID_SPHERE) == 0 &&
		line_matches_predicates(words, sphere_predicates))
		return (RD_ET_SPHERE);
	if (ft_strcmp(words[0], RD_ID_PLANE) == 0 &&
		line_matches_predicates(words, plane_predicates))
		return (RD_ET_PLANE);
	if (ft_strcmp(words[0], RD_ID_CYLINDER) == 0 &&
		line_matches_predicates(words, cylinder_predicates))
		return (RD_ET_CYLINDER);
	return (RD_ET_UNEXPECTED);
}
