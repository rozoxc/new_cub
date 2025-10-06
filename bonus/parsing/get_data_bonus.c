/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:17:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 19:21:44 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	first_arg(char *key)
{
	if (!key)
		return (false);
	if (ft_strcmp(key, "NO") == 0)
		return (true);
	else if (ft_strcmp(key, "SO") == 0)
		return (true);
	else if (ft_strcmp(key, "WE") == 0)
		return (true);
	else if (ft_strcmp(key, "EA") == 0)
		return (true);
	else if (ft_strcmp(key, "DO") == 0)
		return (true);
	else if (ft_strcmp(key, "F") == 0)
		return (true);
	else if (ft_strcmp(key, "C") == 0)
		return (true);
	return (false);
}

char	**split_arg(char *line)
{
	char	**tokens;
	int		i;
	int		start;
	int		len;

	i = 0;
	tokens = ft_malloc(sizeof(char *) * 3, 1);
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && (i - start) < 2)
		i++;
	len = i - start;
	tokens[0] = ft_malloc(len + 1, 1);
	ft_strlcpy(tokens[0], line + start, len + 1);
	if (!first_arg(tokens[0]))
		return (NULL);
	while (line[i] && line[i] == ' ')
		i++;
	tokens[1] = ft_strtrim(line + i);
	tokens[2] = NULL;
	return (tokens);
}

static int	load_extra_textures(t_vars *var)
{
	if (!set_texture(&var->tex.Hands, "textures/hands.xpm"))
		return (err("Invalid or duplicate item"), 0);
	if (!set_texture(&var->tex.shoot0, "textures/shoot0.xpm"))
		return (err("Invalid or duplicate item"), 0);
	if (!set_texture(&var->tex.shoot1, "textures/shoot1.xpm"))
		return (err("Invalid or duplicate item"), 0);
	if (!set_texture(&var->tex.door, "textures/doors.xpm"))
		return (err("Invalid or duplicate item"), 0);
	return (1);
}

int	parse_header(t_vars *var)
{
	char	*line;
	char	**tokens;
	int		items_found;

	items_found = 0;
	while (items_found < 7)
	{
		line = NULL;
		line = get_next_line(var->fd);
		if (!line)
			return (err("Missing header items"), 0);
		if (ft_strlen(line) == 0 || is_whitespace_only(line))
			continue ;
		tokens = split_arg(line);
		if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
			return (err("Invalid line format"), 0);
		if (set_item(var, tokens[0], tokens[1]))
			items_found++;
		else
			return (err("Invalid or duplicate item"), 0);
	}
	if (!load_extra_textures(var))
		return (0);
	return (1);
}
