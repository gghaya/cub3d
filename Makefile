CC = cc
FLAGS =   -fsanitize=address -g

SRCS = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing.c cub_utils/utils.c cub_utils/parsing_utils.c cub3d.c \
		cub_utils/path_parsing_utils.c parsing/rgb_parsing.c parsing/path_parsing.c cub_utils/map_utils.c \
		Libft/ft_split.c Libft/ft_atoi.c Libft/ft_isdigit.c  raycasting/raycasting.c \
		graphics/put_pixels.c graphics/put_pixels1.c 

OBJS = $(SRCS:.c=.o)
NAME = CUB3D
HEADERS = includes/cub3d.h get_next_line/get_next_line.h Libft/libft.h
LIBFTDIR = ft_libft
LIBFT = ${LIBFTDIR}/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(HEADERS) ${LIBFT}
	$(CC) $(FLAGS) $(OBJS) -L ${LIBFTDIR} -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)


${LIBFT}:
	${MAKE} -C ${LIBFTDIR}

%.o: %.c $(HEADERS) 
	$(CC) -Imlx -I $(FLAGS) -c $< -o $@

clean:
	rm -f  $(OBJS)
	${MAKE} clean -C ${LIBFTDIR}

fclean: clean
	rm -f  $(NAME)
	${MAKE} fclean -C ${LIBFTDIR}

re: fclean all