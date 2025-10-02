NAME = cub3d
CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address
MLX_DIR = minilibx-linux
MLX_FLAG = -L$(MLX_DIR) -lXext -lX11 -lm
INCLUDE = includes/cub3d.h

# Mandatory part sources
SRC = mandatory/main.c \
	  mandatory/rycasting/hooks.c \
	  mandatory/rycasting/hooks_utlis.c \
	  mandatory/rycasting/render.c \
	  mandatory/rycasting/rycast.c \
	  mandatory/rycasting/dda_algo.c \
	  mandatory/rycasting/dda_algo_utlis.c \
	  mandatory/rycasting/texturs.c \
	  mandatory/rycasting/utlis.c \
	  mandatory/rycasting/utlis_rycast.c \
	  mandatory/parsing/error.c \
	  mandatory/parsing/get_data.c \
	  mandatory/parsing/map_process.c \
	  mandatory/parsing/parse.c \
	  mandatory/parsing/utils.c \
	  mandatory/parsing/validate_file.c 

# Bonus part sources
BONUS = bonus/main.c \
		bonus/raycasting/hooks_bonus.c \
		bonus/raycasting/draw_bonus.c \
		bonus/raycasting/render_bonus.c \
		bonus/raycasting/utlis_bonus.c \
		bonus/raycasting/rycast_bonus.c \
		bonus/raycasting/dda_algo_bonus.c \
		bonus/raycasting/texturs_bonus.c \
		bonus/parsing/error_bonus.c \
		bonus/parsing/map_process_bonus.c \
		bonus/parsing/utils_bonus.c \
		bonus/parsing/get_data_bonus.c \
		bonus/parsing/parse_bonus.c \
		bonus/parsing/validate_file_bonus.c \
		bonus/parsing/doors.c

HEADER = includes/cub3d.h get_next_line/get_next_line.h
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX_FLAG) libft/libft.a $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/libmlx.a -o $(NAME)

bonus: $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(MLX_FLAG) libft/libft.a $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/libmlx.a -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re