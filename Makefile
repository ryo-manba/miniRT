NAME		:=	miniRT
CC			:=	gcc
CFLAGS		=	-Werror -Wall -Wextra $(INC)
INC			=	-I$(X11) -I$(MLX) -I$(LIBFT)
X11			:=	/usr/X11/include
LIBFT		:=	libft
SRCS		:=	main.c \
				mlx_utils.c \
				color.c \

OBJS		:=	$(SRCS:.c=.o)
MLX			:=	minilibx-linux
LIBS		:=	-L$(LIBFT) -L$(MLX) -lmlx_Darwin -L/$(X11)/../lib -lXext -lX11 -lm
RM 			:=	rm -f

all: $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLX)

$(LIBFT):
		make -C ./libft

clean:
	$(RM) $(OBJS)

cleanlib:
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)

bonus: all

re: fclean all

test: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re bonus
