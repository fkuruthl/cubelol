CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address  -Iminilibx_opengl_20191021

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx_opengl_20191021
MLX = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

INFILES = main.c \
          cub3d.c \
          get_next_line.c \
          get_next_line_utils.c \
		  exit_error.c\
		  path_struct.c\
		  validate.c\
		  pre_exec.c

OBJFILES = $(INFILES:.c=.o)

NAME = cub3d

all: $(LIBFT) $(NAME)

$(NAME): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJFILES)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
