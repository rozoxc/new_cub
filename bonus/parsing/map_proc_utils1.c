/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_proc_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:28:23 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 20:01:33 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	process_line(char *line, char **lines, size_t *count, size_t *max)
{
	size_t	len;

	if (*count == 0 && (is_whitespace_only(line) || *line == '\n'))
		return (0);
	if (*count > 0 && (is_whitespace_only(line) || *line == '\n'))
	{
		ft_malloc(0, 0);
		return (err("Empty line inside map is forbidden\n"), -1);
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	lines[*count] = ft_strdup(line);
	if (ft_strlen(lines[*count]) > *max)
		*max = ft_strlen(lines[*count]);
	(*count)++;
	return (1);
}

bool	read_loop(t_vars *vars, char **lines, \
	size_t *l_count, size_t *max_width)
{
	char	*line;
	int		validation;
	size_t	capacity;

	capacity = 16;
	lines = ft_malloc(sizeof(char *) * capacity, 1);
	line = get_next_line(vars->fd);
	while (line != NULL)
	{
		validation = process_line(line, lines, l_count, max_width);
		if (validation == 0)
		{
			line = get_next_line(vars->fd);
			continue ;
		}
		if (validation == -1)
			return (false);
		if (*l_count >= capacity)
			lines = resize_and_copy(lines, &capacity, *l_count);
		if (!lines)
			return (NULL);
		line = get_next_line(vars->fd);
	}
	return (true);
}

char	**read_map_lines(t_vars *vars, size_t *line_count, \
	size_t *max_width)
{
	char	**lines;

	if (!lines)
		return (err("Memory allocation failed\n"), NULL);
	*line_count = 0;
	*max_width = 0;
	if (!read_loop(vars, lines, line_count, max_width))
		return (NULL);
	if (*line_count == 0)
		return (err("Map not found in file\n"), ft_malloc(0, 0), NULL);
	return (lines);
}

int	create_padded_map(t_vars *vars, char **tmp_lines)
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

int	handle_player_position(t_game *vars, size_t x, size_t y, \
	int *player_count)
{
	if (*player_count > 0)
		return (err("Multiple player positions found.\n"), 0);
	vars->player->posX = x + 0.5;
	vars->player->posY = y + 0.5;
	init_player_direction(vars->player, vars->vars->map[y][x]);
	vars->player->player_dir = vars->vars->map[y][x];
	*player_count = 1;
	vars->vars->map[y][x] = '0';
	return (1);
}
