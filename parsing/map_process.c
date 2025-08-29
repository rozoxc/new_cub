/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 04:08:24 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/24 22:45:22 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'D' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}


static char	**read_map_lines(t_vars *vars, size_t *line_count, size_t *max_width)
{
	char	*line;
	char	**lines;
	size_t	capacity;
    size_t  len;

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
			// free(line);
			continue ;
		}

		if (*line_count > 0 && (is_whitespace_only(line) || *line == '\n'))
		{
			while ((*line_count)-- > 0) free(lines[*line_count]);
			free(lines);
			free(line);
			return (err("Empty line inside map is forbidden\n"), NULL);
		}
		if (*line_count >= capacity)
		{
			// I need to implement it
		}
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

		lines[*line_count] = ft_strdup(line); 
        
		if (ft_strlen(lines[*line_count]) > *max_width)
			*max_width = ft_strlen(lines[*line_count]);
		(*line_count)++;
		// free(line);
	}
	if (*line_count == 0)
		return (err("Map not found in file\n"), free(lines), NULL);

	// for (int i = 0; lines[i] !=  NULL ; i++)
	// 	printf ("\n\n%s\n", lines[i]);
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
				// vars->player.pl  player_x = x;
				// vars->player_y = y;
				    vars->player->posX = y + 0.5;
					vars->player->posY = x + 0.5;
					vars->player->plan_x = 0.60;
					vars->player->plan_y = 0;
					vars->player->player_dir = vars->vars->map[y][x];
					player_count = 1;
			}
		}
		// {
		// 	// if (!is_valid_map_char(vars->vars->map[y][x]))
		// 	// 	return (err("Invalid character in map.\n"), 0);
		// }
	}
	// if (player_count == 0)
	// 	return (err("No player start position found in map.\n"), 0);
	// printf ("Player Position: X: %f, Y: %f\n", vars->player->posX, vars->player->posY);
	// exit (0);
	return (1);
}

int	parse_map(t_game *game)
{
	char	**tmp_lines;
	size_t	i;

	tmp_lines = read_map_lines(game->vars, &game->vars->map_h, &game->vars->map_w);
	if (!tmp_lines)
		return (0);

	if (!create_padded_map(game->vars, tmp_lines))
	{
		// Cleanup tmp_lines on failure
		return (err("Map creation failed.\n"), 0);
	}
		// free(tmp_lines[i++]);
	// free(tmp_lines);
	
	if (!process_map_content(game))
		return (0);
	
	if (!validate_map_walls(game))
		return (0);

	// vars->map[vars->player_y][vars->player_x] = '0';
	return (1);
}




static int	flood_fill(char **map_copy, t_vars *vars, size_t x, size_t y)
{
	if (x < 0 || x >= vars->map_w || y < 0 || y >= vars->map_h)
		return (0);

	if (map_copy[y][x] == ' ')
		return (0);

	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return (1);

	map_copy[y][x] = 'F';

	if (flood_fill(map_copy, vars, x + 1, y) == 0)
		return (0);
	if (flood_fill(map_copy, vars, x - 1, y) == 0)
		return (0);
	if (flood_fill(map_copy, vars, x, y + 1) == 0)
		return (0);
	if (flood_fill(map_copy, vars, x, y - 1) == 0)
		return (0);
	return (1);
}

static int	validate_map_walls(t_game *game)
{
	char	**map_copy;
	size_t	i;
	int		is_closed;

	map_copy = ft_malloc(sizeof(char *) * (game->vars->map_h + 1), 1);
	if (!map_copy)
		return (0);
	i = 0;
	while (i < game->vars->map_h)
	{
		map_copy[i] = ft_strdup(game->vars->map[i]);
		if (!map_copy[i])
		{

			while (i-- > 0)
				free(map_copy[i]);
			return (free(map_copy), 0);
		}
		i++;
	}
	map_copy[i] = NULL;
	
	is_closed = flood_fill(map_copy, game->vars, game->player->posX - 0.5, game->player->posY - 0.5);

	// Free the copied map
	i = 0;
	// while (i < vars->map_h)
	// 	free(map_copy[i++]);
	// free(map_copy);
	
	if (!is_closed)
		return (err("Map is not surrounded by walls.\n"), 0);
	return (1);
}
