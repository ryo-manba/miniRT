NAME		:=	miniRT
CC			:=	gcc
CFLAGS		=	-Werror -Wall -Wextra $(INC) -g -fsanitize=address
INC			=	-I$(X11) -I$(MLX) -I$(LIBFT)
X11			:=	/usr/X11/include
LIBFT		:=	libft
LIBFT_A		:=	$(LIBFT).a
LIBREAD		:=	libread
LIBREAD_A	:=	$(LIBREAD).a
SRCS		:=	debug.c \
				main.c \
				mr_mlx_utils.c \
				mr_vec3_utils.c \
				mr_vec3_operator.c \
				rt_color.c \
				rt_object_sphere.c \
				rt_object_plane.c \
				rt_object_cylinder.c \
				rt_hit_util.c \
				rt_vector_rotation.c \
				rt_is_shadow.c \
				rt_texture_plane.c \
				rt_texture_sphere.c \
				rt_texture_cylinder.c \
				rt_ambient.c \
				rt_diffuse.c \
				rt_specular.c \



OBJS		:=	$(SRCS:.c=.o)
MLX			:=	minilibx-linux
LIBS		:=	-L$(LIBFT) -L$(MLX) -lmlx_Darwin -L/$(X11)/../lib -lXext -lX11 -lm
RM 			:=	rm -f

all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT_A) $(LIBREAD_A)
	make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LIBREAD_A) $(LIBS) -o $(NAME)

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX)

$(LIBFT):
		make -C ./libft

$(LIBFT_A):	$(LIBFT)
		cp ./libft/$(LIBFT_A) .

$(LIBREAD):
		make -C ./rd

$(LIBREAD_A):	$(LIBREAD)
		cp ./rd/$(LIBREAD_A) .

clean:
	$(RM) $(OBJS)

cleanlib:
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME) $(LIBFT_A) $(LIBREAD_A)

bonus: all

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re bonus
