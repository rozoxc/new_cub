NAME = cub3d
NAME_BONUS = cub3d_bonus
CC = cc 
FLAGS = -Wall -Werror -Wextra #-fsanitize=address
MLX_DIR = minilibx-linux
LIBFT = libft/libft.a
HEADER = libft/libft.h libft/get_next_line.h includes/cub3d.h 

MLX_FLAG = -L$(MLX_DIR) -lXext -lX11 -lm
INCLUDE = includes/cub3d.h

SRCLIB = libft/ft_lstadd_back_bonus.c libft/ft_lstsize_bonus.c libft/ft_strjoin.c libft/ft_atoi.c libft/ft_lstadd_front_bonus.c  libft/ft_strcmp.c libft/ft_strcpy.c libft/ft_memcpy.c libft/ft_memset.c libft/ft_strtrim.c \
			libft/ft_lstlast_bonus.c libft/ft_lstnew_bonus.c libft/ft_split.c libft/ft_strdup.c libft/ft_strlen.c libft/ft_isdigit.c libft/get_next_line.c libft/get_next_line_utils.c libft/grb_coll.c libft/ft_strlcpy.c
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
	  mandatory/rycasting/clean.c \
	  mandatory/parsing/error.c \
	  mandatory/parsing/get_data.c \
	  mandatory/parsing/map_process.c \
	  mandatory/parsing/parse.c \
	  mandatory/parsing/utils.c \
	  mandatory/parsing/getData_Utils.c\
	  mandatory/parsing/map_process_Utils.c\
	  mandatory/parsing/map_process_Utils2.c\
	  mandatory/parsing/validate_file.c\
	  mandatory/parsing/read_map.c


# Bonus part sources
BONUS = bonus/main.c \
		bonus/raycasting/hooks_bonus.c \
		bonus/raycasting/hooks_utlis_bonus.c\
		bonus/raycasting/render_bonus.c \
		bonus/raycasting/render_utlis_bonus.c \
		bonus/raycasting/utlis_bonus.c \
		bonus/raycasting/rycast_bonus.c \
		bonus/raycasting/rycast_utlis_bonus.c \
		bonus/raycasting/dda_algo_bonus.c \
		bonus/raycasting/dda_algo_utlis_bonus.c\
		bonus/raycasting/texturs_bonus.c \
		bonus/raycasting/utlis_bonus_2.c \
		bonus/raycasting/utlis_bonus_3.c \
		bonus/raycasting/clean_bonus.c \
		bonus/parsing/error_bonus.c \
		bonus/parsing/map_process_bonus.c \
		bonus/parsing/utils_bonus.c \
		bonus/parsing/get_data_bonus.c \
		bonus/parsing/parse_bonus.c \
		bonus/parsing/validate_file_bonus.c \
		bonus/parsing/doors.c\
		bonus/parsing/get_data_utils.c\
		bonus/parsing/map_proc_utils.c\
		bonus/parsing/map_proc_utils1.c\
		bonus/parsing/map_proc_utils2.c\
		bonus/parsing/doors_utils.c\
		bonus/parsing/doors_utils1.c\






OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT) 
	$(CC) $(FLAGS) $(OBJ) $(MLX_FLAG) $(LIBFT) $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/libmlx.a -o $(NAME)

bonus: $(OBJ_BONUS) $(LIBFT) 
	$(CC) $(FLAGS) $(OBJ_BONUS) $(MLX_FLAG) $(LIBFT) $(MLX_DIR)/libmlx_Linux.a $(MLX_DIR)/libmlx.a -o $(NAME_BONUS)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Iincludes -c $< -o $@

$(LIBFT): $(SRCLIB) $(HEADER)
	make -C libft/ 

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make -C libft/ fclean

re: fclean all bonus

.PHONY: all bonus clean fclean re