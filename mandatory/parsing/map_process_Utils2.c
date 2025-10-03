/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_process_Utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:08:44 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 17:27:12 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	init_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		1 && (player->dir_x = 0, player->dir_y = -1);
		1 && (player->plan_x = 0.66, player->plan_y = 0);
	}
	else if (dir == 'S')
	{
		1 && (player->dir_x = 0, player->dir_y = 1);
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

static char	**read_map_lines(t_vars *vars, size_t *line_count, \
	size_t *max_width)
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

int	fill_player_info__check_char(t_vars *vars, int *player_count)
{
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
				continue ;
			if (!fill_player_info__check_char(vars, &player_count))
				return (0);
		}
	}
	if (player_count == 0)
		return (err("No player start position found in map.\n"), 0);
	return (1);
}
