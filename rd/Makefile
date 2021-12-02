CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror -g -fsanitize=undefined
NAME		:=	libread.a
SRCS		:=	rd_file.c \
				rd_error.c \
				rd_scene.c \
				rd_scene_utils.c \
				rd_vector.c \
				rd_element_predicate.c \
				rd_scalar_predicate.c rd_vector_predicate.c rd_double.c \
				rd_extractor.c \
				rd_debug.c

OBJS		:=	$(SRCS:.c=.o)

TEST_NAME	:=	a.out
TEST_SRCS	:=	main.c
TEST_OBJS	:=	$(TEST_SRCS:.c=.o)

LIBFT_DIR	:=	../libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	ar rcs $(NAME) $(OBJS)

t			:	$(TEST_NAME)

$(TEST_NAME):	$(OBJS) $(TEST_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(TEST_NAME) $(LIBFT) $(OBJS) $(TEST_OBJS)

$(LIBFT)	:
	$(MAKE) -C $(LIBFT_DIR)

clean		:
	$(RM) -rf $(OBJS) $(TEST_OBJS)

fclean		:	clean
	$(RM) $(NAME)

re			:	fclean all
