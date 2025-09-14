NAME = cub3d
CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address
MLX_DIR = minilibx-linux
MLX_FLAG =  -L$(MLX_DIR) -lXext -lX11 -lm
INCLUDE = includes/cub3d.h
SRC = src/main.c \
	  mandatory/rycasting/hooks.c  \
	  mandatory/rycasting/draw.c \
	  mandatory/rycasting/render.c \
	  mandatory/rycasting/rycast.c \
	  mandatory/rycasting/dda_algo.c \
	  mandatory/rycasting/texturs.c\
	  mandatory/rycasting/utlis_rycast.c \
	  mandatory/parsing/error.c         mandatory/parsing/get_data.c      mandatory/parsing/map_process.c   mandatory/parsing/parse.c        mandatory/parsing/utils.c         mandatory/parsing/validate_file.c


BONUS = src_bonus/main.c \
		bonus/hooks_bonus.c \
		bonus/draw_bonus.c \
		bonus/render_bonus.c \
		bonus/utlis_bonus.c \
		bonus/rycast_bonus.c \
		bonus/dda_algo_bonus.c \
		bonus/texturs_bonus.c \
		bonus/parsing/error_bonus.c \
		bonus/parsing/map_process_bonus.c\
		bonus/parsing/utils_bonus.c\
		bonus/parsing/get_data_bonus.c\
		bonus/parsing/parse_bonus.c\
		bonus/parsing/validate_file_bonus.c



HEADER = includes/cub3d.h get_next_line/get_next_line.h
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all : $(NAME)

bonus : $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(MLX_FLAG) libft/libft.a minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a  -o $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX_FLAG) libft/libft.a minilibx-linux/libmlx_Linux.a minilibx-linux/libmlx.a -o $(NAME)


%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -f $(NAME)
re : fclean
	make
.PHONY : clean