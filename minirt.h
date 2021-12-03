#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <X11/X.h>
# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "rt_scene.h"
# include "mr_vec3.h"

/* window size */
//# define WIDTH 500
//# define HEIGHT 500

/* keycode */
# ifdef __linux__
#  define KEY_ESC 65307
# else
#  define KEY_ESC 53
# endif

/* colorcode */
# define BLACK 0x000000
# define WHITE 0xffffff

/* hooks */
void	mr_mlx_pixel_put(t_img *img, int x, int y, int color);
int		mr_exit_window(t_info *info);


/* color */
int rt_create_trgb(int t, int r, int g, int b);
int	rt_get_trgb(int trgb, int shift);
int	rt_add_shade(double distance, int color);
int	rt_get_opposite(int color);

/* mr_sphere */
bool	rt_hit_sphere(const t_vec3 *center, double radius, const t_ray *ray, t_hit_record *rec);

bool	rt_hit_plain(
			const t_vec3 *center,
			const t_vec3 *normal,
			const t_ray *ray,
			t_hit_record *rec);


/* debug */
void	vec3_debug(t_vec3 *vec);

#endif
