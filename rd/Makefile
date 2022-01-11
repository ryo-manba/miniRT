CC			:=	gcc
MLX			:=	../minilibx-linux
X11			:=	/usr/X11/include
INC			:=	-I$(X11) -I$(MLX) -I../includes -I../common -I../libft
LIBS		:=	-L../libft -L$(MLX) -L/$(X11)/../lib -lXext -lX11 -lm
CFLAGS		:=	-Wall -Wextra -Werror -g -fsanitize=address $(INC)
NAME		:=	libread.a
SRCS		:=	rd_file.c \
				rd_error.c \
				rd_scene.c \
				rd_after_read.c \
				rd_scene_destroyer.c \
				rd_vector.c \
				rd_element_predicate.c \
				rd_scalar_predicate.c rd_vector_predicate.c rd_double.c \
				rd_extractor.c \
				rd_element_slot.c \
				rd_field_extractor.c \
				rd_attach_attribute.c \
				rd_after_extraction.c \
				rd_debug.c

OBJS		:=	$(SRCS:.c=.o)

LIBFT_DIR	:=	../libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(MLX)
	ar rcs $(NAME) $(OBJS)

$(LIBFT)	:
	$(MAKE) -C $(LIBFT_DIR)

$(MLX)		:
	$(MAKE) -C $(MLX)

clean		:
	$(RM) -rf $(OBJS) $(TEST_OBJS)

fclean		:	clean
	$(RM) $(NAME)

re			:	fclean all

.PHONY		:	name norm
name		: $(NAME)
	nm -u $(NAME)

norm		:
	python3 -m norminette
