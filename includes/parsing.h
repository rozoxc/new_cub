/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:22:47 by student           #+#    #+#             */
/*   Updated: 2025/09/22 09:21:20 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>

# include "../libft/libft.h"
#include "../libft/get_next_line.h"

#include "cub3d.h"

# define WALL 1
# define EMPTY 0
# define SPACE_IN_MAP 2
# define DOOR 3


# define NORTH_IN_MAP 4
# define SOUTH_IN_MAP 5
# define WEST_IN_MAP 6
# define EAST_IN_MAP 7


# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR_TEX 4




// typedef struct s_rgb
// {
// 	int	r;
// 	int	g;
// 	int	b;
// }	t_rgb;


// typedef struct s_textures
// {
// 	char	*north;
// 	char	*south;
// 	char	*west;
// 	char	*east;
// 	char	*door;
// }	t_textures;


// typedef struct s_player{
//     double plan_x;
//     double plan_y;
//     // double dir_x;
//     // double dir_y;
//     double posX;
//     double posY;
// 	char		player_dir;
// } t_player;


// typedef struct s_vars
// {
// 	t_textures	tex;
// 	t_rgb		floor;
// 	t_rgb		ceiling;
// 	char		**map;		
// 	size_t		map_h;	
// 	size_t		map_w;	
// 	// int			player_x;	
// 	// int			player_y;
// 	// char		player_dir;
// 	int			fd;


// 	t_player player;



	
// }	t_vars;





// int			parser(char *file);
// int validate_path_and_open(char *path, t_vars *var);
// int parse_header(t_vars *var);
// int is_valid_rgb(char *str);
// int count_char(char *str, char c);
// int is_whitespace_only(char *str);
// void init_vars(t_vars *var);
// void	err(char *error);
// int parse_map(t_vars *var);
// int is_valid_map_char(char c);
// int is_player_char(char c);



// static int		validate_map_walls(t_vars *vars);
// static int	validate_map_walls(t_vars *vars);

#endif