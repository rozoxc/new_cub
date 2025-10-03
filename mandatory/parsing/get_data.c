/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:17:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 17:30:22 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	set_texture(char **texture_ptr, char *path)
{
	int	fd;

	fd = -1;
	if (*texture_ptr != NULL)
		return (0);
	printf ("%s|\n", path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	*texture_ptr = ft_strdup(path);
	return (*texture_ptr != NULL);
}

bool	firstarg(char *key)
{
	if (!key)
		return (NULL);
	if (ft_strcmp(key, "NO") == 0)
		return (true);
	else if (ft_strcmp(key, "SO") == 0)
		return (true);
	else if (ft_strcmp(key, "WE") == 0)
		return (true);
	else if (ft_strcmp(key, "EA") == 0)
		return (true);
	else if (ft_strcmp(key, "F") == 0)
		return (true);
	else if (ft_strcmp(key, "C") == 0)
		return (true);
	return (false);
}

char	**splitarg(char *line)
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
	if (!firstarg(tokens[0]))
		return (write(2, "Invalid line format", 20), NULL);
	while (line[i] && line[i] == ' ')
		i++;
	tokens[1] = ft_strtrim(line + i);
	tokens[2] = NULL;
	return (tokens);
}

int	parse_header(t_vars *var)
{
	char	*line;
	char	**tokens;
	int		items_found;

	items_found = 0;
	while (items_found < 6)
	{
		line = get_next_line(var->fd);
		if (!line)
			return (err("Missing header items"), 0);
		if (ft_strlen(line) == 0 || is_whitespace_only(line))
		{
			line = NULL;
			continue ;
		}
		tokens = splitarg(line);
		if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
			return (err("Invalid line format"), 0);
		if (set_item(var, tokens[0], tokens[1]))
			items_found++;
		else
			return (err("Invalid or duplicate item"), 0);
	}
	return (1);
}
