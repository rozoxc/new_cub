NAME = cub3d
CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=address
MLX_FLAG =  -lmlx -framework OpenGL -framework AppKit
INCLUDE = includes/cub3d.h
SRC = src/main.c \
	  rycasting/hooks.c  \
	  rycasting/draw.c \
	  rycasting/render.c \
	  rycasting/rycast.c \
	  rycasting/dda_algo.c \
	  rycasting/texturs.c\
	  rycasting/utlis_rycast.c \
	  parsing/error.c         parsing/get_data.c      parsing/map_process.c   parsing/parse.c        parsing/utils.c         parsing/validate_file.c


BONUS = bonus/main_bonus.c \
		bonus/hooks_bonus.c \
		bonus/draw_bonus.c \
		bonus/render_bonus.c \
		bonus/utlis_bonus.c \
		bonus/rycast_bonus.c \
		bonus/dda_algo_bonus.c \
		bonus/texturs_bonus.c 


HEADER = includes/cub3d.h get_next_line/get_next_line.h
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)
all : $(NAME)
bonus : $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(MLX_FLAG) libft/libft.a -o $(NAME)


$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX_FLAG) libft/libft.a -o $(NAME)
%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
fclean : clean
	rm -f $(NAME)
.PHONY : clean