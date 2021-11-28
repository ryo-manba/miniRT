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

/* window size */
# define WIDTH 500
# define HEIGHT 500

/* keycode */
# ifdef __linux__
#  define KEY_SPACE 32
#  define KEY_B 98
#  define KEY_D 100
#  define KEY_G 103
#  define KEY_I 105
#  define KEY_R 114
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_SHIFT 65505
#  define KEY_CONTROL 65507
#  define MOUSE_CLICK 2
# else
#  define KEY_D 2
#  define KEY_G 5
#  define KEY_B 11
#  define KEY_R 15
#  define KEY_I 34
#  define KEY_ESC 53
#  define KEY_SPACE 49
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_CONTROL 256
#  define KEY_SHIFT 257
#  define MOUSE_CLICK 3
# endif

/* mousecode */
# define SCROLL_UP 4
# define SCROLL_DOWN 5

/* colorcode */
# define BLACK 0x000000
# define WHITE 0xffffff

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_rgb {
	int	r;
	int	g;
	int	b;
}	t_rgb;

/* hooks */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* color */
int create_trgb(int t, int r, int g, int b);
int	get_trgb(int trgb, int shift);
int	add_shade(double distance, int color);
int	get_opposite(int color);

#endif
