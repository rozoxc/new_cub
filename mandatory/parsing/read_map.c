/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:05:16 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 14:36:08 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**resize_lines_array(char **lines, size_t *capacity, \
	size_t line_count)
{
	char	**new_lines;
	size_t	i;

	*capacity *= 2;
	new_lines = ft_malloc(sizeof(char *) * (*capacity), 1);
	if (!new_lines)
	{
		ft_malloc(0, 0);
		return (err("Memory reallocation failed\n"), NULL);
	}
	i = 0;
	while (i < line_count)
	{
		new_lines[i] = lines[i];
		i++;
	}
	return (new_lines);
}

int	process_line_validation(char *line, size_t line_count)
{
	if (line_count == 0 && (is_whitespace_only(line) || *line == '\n'))
		return (0);
	if (line_count > 0 && (is_whitespace_only(line) || *line == '\n'))
	{
		ft_malloc(0, 0);
		err("Empty line inside map is forbidden\n");
		return (-1);
	}
	return (1);
}

char	*process_and_store_line(char *line, char **lines, \
	size_t *line_count, size_t *max_width)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	lines[*line_count] = ft_strdup(line);
	if (ft_strlen(lines[*line_count]) > *max_width)
		*max_width = ft_strlen(lines[*line_count]);
	(*line_count)++;
	return (lines[*line_count - 1]);
}

char	**process_map_lines(t_vars *vars, t_map_reader *reader)
{
	char	*line;
	int		validation;

	line = get_next_line(vars->fd);
	while (line != NULL)
	{
		validation = process_line_validation(line, *reader->line_count);
		if (validation == -1)
			return (NULL);
		if (validation == 0)
		{
			line = get_next_line(vars->fd);
			continue ;
		}
		if (*reader->line_count >= reader->capacity)
			reader->lines = resize_lines_array(reader->lines, \
				&reader->capacity, *reader->line_count);
		if (!reader->lines)
			return (NULL);
		process_and_store_line(line, reader->lines, \
			reader->line_count, reader->max_width);
		line = get_next_line(vars->fd);
	}
	return (reader->lines);
}

char	**read_map_lines(t_vars *vars, size_t *line_count, \
	size_t *max_width)
{
	t_map_reader	reader;

	reader.capacity = 16;
	reader.lines = ft_malloc(sizeof(char *) * reader.capacity, 1);
	if (!reader.lines)
		return (err("Memory allocation failed\n"), NULL);
	reader.line_count = line_count;
	reader.max_width = max_width;
	1 && (*line_count = 0, *max_width = 0);
	reader.lines = process_map_lines(vars, &reader);
	if (!reader.lines)
		return (NULL);
	if (*line_count == 0)
		return (err("Map not found in file\n"), ft_malloc(0, 0), NULL);
	return (reader.lines);
}
