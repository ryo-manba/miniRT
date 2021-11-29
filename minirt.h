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
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* color */
int create_trgb(int t, int r, int g, int b);
int	get_trgb(int trgb, int shift);
int	add_shade(double distance, int color);
int	get_opposite(int color);

/* mr_sphere */
double	rt_hit_sphere(const t_vec3 *center, double radius, const t_ray *ray);


#endif
