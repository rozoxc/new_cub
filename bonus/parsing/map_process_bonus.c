/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 11:15:52 by selbouka          #+#    #+#             */
/*   Updated: 2025/09/21 13:42:30 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plan_x = 0.66;
		player->plan_y = 0;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plan_x = -0.66;
		player->plan_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plan_x = 0;
		player->plan_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plan_x = 0;
		player->plan_y = -0.66;
	}
}

/* Updated functions for map_process_bonus.c */
static int	ft_end_with_one(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = vars->map;
	while (i < vars->map_h)
	{
		j = vars->map_w - 1;
		while (j >= 0 && map[i][j] == ' ')
			j--;
		if (j >= 0 && map[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'D' || c == 'd' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// Updated check for door surroundings
static int	ft_check_zero_surroundings(char **map, int i, int j, t_vars *vars)
{
	// Check right boundary
	if (j + 1 >= vars->map_w || map[i][j + 1] == ' ')
		return (0);
	// Check left boundary  
	if (j > 0 && map[i][j - 1] == ' ')
		return (0);
	// Check top boundary
	if (i > 0 && map[i - 1][j] == ' ')
		return (0);
	// Check bottom boundary
	if (i + 1 < vars->map_h && map[i + 1][j] == ' ')
		return (0);
	return (1);
}

// Updated validation function to handle doors

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static char	**read_map_lines(t_vars *vars, size_t *line_count, size_t *max_width)
{
	char	*line;
	char	**lines;
	char	**new_lines;
	size_t	capacity;
	size_t	len;
	size_t	i;
	
	capacity = 16;
	lines = ft_malloc(sizeof(char *) * capacity, 1);
	if (!lines)
		return (err("Memory allocation failed\n"), NULL);
		*line_count = 0;
	*max_width = 0;
	while ((line = get_next_line(vars->fd)) != NULL)
	{
		if (*line_count == 0 && (is_whitespace_only(line) || *line == '\n'))
		{
			continue ;
		}
		if (*line_count > 0 && (is_whitespace_only(line) || *line == '\n'))
		{
			ft_malloc(0, 0);
			return (err("Empty line inside map is forbidden\n"), NULL);
		}
		
		
		if (*line_count >= capacity)
		{
			capacity *= 2; 
			new_lines = ft_malloc(sizeof(char *) * capacity, 1);
			if (!new_lines)
			{
				ft_malloc(0, 0);
				return (err("Memory reallocation failed\n"), NULL);
			}
			i = 0;
			while (i < *line_count)
			{
				new_lines[i] = lines[i];
				i++;
			}
			lines = new_lines;
		}
		
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
		lines[*line_count] = ft_strdup(line); 
		
		if (ft_strlen(lines[*line_count]) > *max_width)
		*max_width = ft_strlen(lines[*line_count]);
		(*line_count)++;
	}
	if (*line_count == 0)
		return (err("Map not found in file\n"), ft_malloc(0, 0), NULL);
	return (lines);
}

static int	create_padded_map(t_vars *vars, char **tmp_lines)
{
	size_t	i;

	vars->map = ft_malloc(sizeof(char *) * (vars->map_h + 1), 1);
	if (!vars->map)
	return (0);
	i = 0;
	while (i < vars->map_h)
	{
		vars->map[i] = ft_malloc(sizeof(char) * (vars->map_w + 1), 1);
		if (!vars->map[i])
			return (0);

			ft_memset(vars->map[i], ' ', vars->map_w);
		ft_memcpy(vars->map[i], tmp_lines[i], ft_strlen(tmp_lines[i]));
		vars->map[i][vars->map_w] = '\0';
		i++;
	}
	vars->map[i] = NULL;
	return (1);
}

static int	process_map_content(t_game *vars)
{
	size_t	x;
	size_t	y;
	int		player_count;
	
	player_count = 0;
	y = -1;
	while (++y < vars->vars->map_h)
	{
		x = -1;
		while (++x < vars->vars->map_w)
		{
			if (vars->vars->map[y][x] == '\0')
			return (err("Map contains null character.\n"), 0);
			if (vars->vars->map[y][x] == '\n')
			return (err("Map contains newline character.\n"), 0);
			if (vars->vars->map[y][x] == ' ')
			continue;
			if (!is_valid_map_char(vars->vars->map[y][x]))
			return (err("Invalid character in map.\n"), 0);
			if (is_player_char(vars->vars->map[y][x]))
			{
				if (player_count > 0)
				return (err("Multiple player positions found.\n"), 0);
				vars->player->posX = x + 0.5;
				vars->player->posY = y + 0.5;
				init_player_direction(vars->player, vars->vars->map[y][x]);
				vars->player->player_dir = vars->vars->map[y][x];
				player_count = 1;
				vars->vars->map[y][x] = '0';
			}
		}
	}
	if (player_count == 0)
		return (err("No player start position found in map.\n"), 0);
	return (1);
}


static int	ft_only_ones(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1')
		return (0);
		i++;
	}
	return (1);
}


static int	ft_start_with_one(t_vars *vars)
{
	char	**map;
	int		i;
	int		j;
	
	i = 0;
	map = vars->map;
	while (i < vars->map_h)
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
		return (0);
		i++;
	}
	return (1);
}



static int	validate_map_walls_optimized(t_game *game)
	{
		char	**map;
		int		i;
		int		j;
	
		map = game->vars->map;
		
		// Check first row (top boundary)
		if (!ft_only_ones(map[0]))
			return (err("Top boundary must contain only walls and spaces.\n"), 0);
		
		// Check last row (bottom boundary)
		if (!ft_only_ones(map[game->vars->map_h - 1]))
			return (err("Bottom boundary must contain only walls and spaces.\n"), 0);
		
		// Check that each line starts with '1'
		if (!ft_start_with_one(game->vars))
			return (err("Each map line must start with a wall.\n"), 0);
			
		// Check that each line ends with '1'
		if (!ft_end_with_one(game->vars))
			return (err("Each map line must end with a wall.\n"), 0);
		
		// Check all '0', door, and player cells have proper wall surroundings
		i = 1;
		while (i < game->vars->map_h - 1)
		{
			j = 0;
			while (j < game->vars->map_w)
			{
				char cell = map[i][j];
				if (cell == '0' || is_player_char(cell) || cell == 'D' || cell == 'd')
				{
					if (!ft_check_zero_surroundings(map, i, j, game->vars))
						return (err("Map is not properly enclosed by walls.\n"), 0);
				}
				j++;
			}
			i++;
		}
		return (1);
	}

static int validate_door_placement(char **map, int x, int y, int map_w, int map_h)
{
    // Check boundaries - doors can't be on the edges
    if (x <= 0 || x >= map_w - 1 || y <= 0 || y >= map_h - 1)
    {
        printf("❌ Door at (%d, %d) cannot be on map boundary\n", x, y);
        return (0);
    }
    
    // Check if door is between two walls horizontally OR vertically
    int horizontal_walls = (map[y][x-1] == '1' && map[y][x+1] == '1');
    int vertical_walls = (map[y-1][x] == '1' && map[y+1][x] == '1');
    
    // Door must be between walls in exactly one direction
    if (!horizontal_walls && !vertical_walls)
    {
        printf("❌ Door at (%d, %d) is not between two walls\n", x, y);
        return (0);
    }
    
    // Make sure door is not in a corner or surrounded by walls
    if (horizontal_walls && vertical_walls)
    {
        printf("❌ Door at (%d, %d) is surrounded by walls (invalid placement)\n", x, y);
        return (0);
    }
    
    return (1);
}

// Add door validation to your existing validation function
static int validate_all_doors(t_game *game)
{
    int x, y;
    int door_count = 0;
    
    for (y = 0; y < game->vars->map_h; y++)
    {
        for (x = 0; x < game->vars->map_w; x++)
        {
            char cell = game->vars->map[y][x];
            if (cell == 'D' || cell == 'd')
            {
                if (!validate_door_placement(game->vars->map, x, y, 
                                           game->vars->map_w, game->vars->map_h))
                {
                    return (0);
                }
                door_count++;
            }
        }
    }
    
    if (door_count > 0)
        printf("✅ Found %d valid doors in map\n", door_count);
    
    return (1);
}

int parse_map(t_game *game)
{
    char **tmp_lines;
    
    tmp_lines = read_map_lines(game->vars, &game->vars->map_h, &game->vars->map_w);
    if (!tmp_lines)
        return (0);
    
    if (!create_padded_map(game->vars, tmp_lines))
    {
        return (err("Map creation failed.\n"), 0);
    }
    
    if (!process_map_content(game))
        return (0);
    
    if (!validate_map_walls_optimized(game))
        return (0);
	if (!validate_all_doors(game))
   		return (err("Invalid door placement detected.\n"), 0);

    // ADD THIS LINE - Validate door placements
    if (!validate_all_doors(game))
        return (err("Invalid door placement detected.\n"), 0);
    return (1);
}
