#ifndef RT_SCENE_H
# define RT_SCENE_H

#include "mr_vec3.h"
// mr -> main, hook
// rt -> raytracing
// read, rendaring, others

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	t_img	img;
} t_info;

typedef struct	s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	int		pixel_x;
	int		pixel_y;
	t_vec3	marking_color;
} t_ray;

typedef struct	s_textures
{
	double	u;
	double	v;
} t_textures;

typedef struct	s_hit_record
{
	t_vec3		p;
	t_vec3		normal;
	double		t;
	bool		hit;
	double		cos;
	t_vec3		color;
	t_element	element;
	t_textures	tex;
}	t_hit_record;

#endif
