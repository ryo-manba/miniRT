NAME		:=	miniRT
CC			:=	gcc
CFLAGS		=	-Werror -Wall -Wextra $(INC) -g -fsanitize=thread
ifeq ($(BONUS), 1)
CFLAGS		+=	-D BONUS=1 -D THREADS=16
endif
INC			=	-I$(X11) -I$(MLX) -I$(LIBFT) -Iincludes -Icommon -Ird
X11			:=	/usr/X11/include
LIBFT		:=	libft
LIBFT_A		:=	./$(LIBFT)/$(LIBFT).a
LIBREAD		:=	libread
LIBREAD_A	:=	./rd/$(LIBREAD).a

SRCS		:=	debug.c \
				main.c \
				mr_mlx_utils.c \
				mr_mlx_hooks.c \
				mr_vec3_utils.c \
				mr_vec3_operator.c \
				mr_vec3_operator2.c \
				mr_vec3_operator_composit.c \
				mr_reading_imagefile.c \
				mr_error.c \
				rt_raytracer.c \
				rt_color.c \
				rt_light_utils.c \
				rt_reflection.c \
				rt_tangent.c \
				rt_object_sphere.c \
				rt_object_plane.c \
				rt_object_cylinder.c \
				rt_object_paraboloid.c \
				rt_object_cone.c \
				rt_hit_util.c \
				rt_vector_rotation.c \
				rt_is_shadow.c \
				rt_texture_plane.c \
				rt_texture_sphere.c \
				rt_texture_cylinder.c \
				rt_texture_paraboloid.c \
				rt_texture_cone.c \
				rt_ambient.c \
				rt_diffuse.c \
				rt_specular.c \
				rt_coord_util.c \
				rt_equation.c \
				rt_bumpfunc.c \
				rt_fmath.c

OBJS		=	$(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJDIR		:=	./objs/

MLX			:=	minilibx-linux
MLX_BASE	:=	mlx
ifdef FOR_MAC
	MLX_BASE	:=	mlx_Darwin
endif
MLX_A		:= 	./$(MLX)/lib$(MLX_BASE).a
LIBS		:=	-L$(LIBFT) -L$(MLX) -Lrd -l$(MLX_BASE) -L/$(X11)/../lib -lXext -lX11 -lm -lread -lft
RM 			:=	rm -rf
SRCDIR		:= ./srcs/


all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS) $(MLX_A) $(LIBFT_A) $(LIBREAD_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT_A):
	make -C $(LIBFT)

$(LIBREAD_A):
	make -C ./rd

$(MLX_A):
	make -C $(MLX)

$(OBJDIR):
	mkdir -p objs

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

cleanlib:
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME) $(LIBFT_A) $(LIBREAD_A) $(OBJDIR)

re: fclean all

bonus:
	$(MAKE) BONUS=1

re_bonus: fclean bonus

test: $(NAME)
	./test.sh

.PHONY: all clean fclean re bonus re_bonus norm nm nm_grep

norm:
	$(MAKE) -C libft norm
	$(MAKE) -C rd norm
	python3 -m norminette $(SRCDIR) includes common

nm: $(NAME)
	@nm -u $(NAME) \
		| grep -E "^_" | grep -E "^_X" -v | grep -E "^__" -v | cut -b 2- \
		| grep -E '^(open|close|read|write|printf|malloc|free|perror|strerror|exit|cos|sin|tan|asin|acos|atan2|log|pow|fmod|floor|ceil)' -v

nm_grep:
	$(MAKE) nm | xargs -I{} bash -c "echo '[[' {} ']]'; grep {} srcs libft rd -r -w --col -n"
