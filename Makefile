NAME		=	miniRT
CC			=	gcc
CFLAGS		=	-Werror -Wall -Wextra
LIBFT		=	./libft/libft.a
SRCS		=	
OBJS		=	$(SRCS:.c=.o)
MLX			= 	-Imlx
MLXFLAGS	=	-lXext -lX11 -lm -lbsd
MLXPATH		=	./minilibx-linux
RM 			=	rm -f

all: $(NAME)

$(NAME): $(MLXPATH) $(OBJS) $(LIBFT)
	make -C $(MLXPATH)
	$(CC) $(MLX) $(OBJS) $(MLXPATH)/libmlx.a $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

$(MLXPATH):
	git clone https://github.com/42Paris/minilibx-linux.git $(MLXPATH)

$(LIBFT):
		make -C ./libft

clean:
	make clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean re help bonus
