/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:22:05 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/06 19:23:27 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	rgb_to_mlx_color(t_rgb *rgb)
{
	rgb->rgb = ((rgb->r << 16) | (rgb->g << 8) | rgb->b);
}

int	set_texture(char **texture_ptr, char *path)
{
	int	fd;

	if (*texture_ptr != NULL)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	*texture_ptr = ft_strdup(path);
	return (*texture_ptr != NULL);
}

int	set_color(t_rgb *color, char *rgb)
{
	char	**rgb_tokens;

	if (color->r != -1)
		return (0);
	if (count_char(rgb, ',') != 2)
		return (0);
	rgb_tokens = ft_split(rgb, ',');
	if (!rgb_tokens
		|| !rgb_tokens[0]
		|| !rgb_tokens[1]
		|| !rgb_tokens[2]
		|| rgb_tokens[3])
		return (0);
	if (!is_valid_rgb(rgb_tokens[0])
		|| !is_valid_rgb(rgb_tokens[1])
		|| !is_valid_rgb(rgb_tokens[2]))
		return (0);
	color->r = ft_atoi(rgb_tokens[0]);
	color->g = ft_atoi(rgb_tokens[1]);
	color->b = ft_atoi(rgb_tokens[2]);
	return (1);
}

int	set_item(t_vars *var, char *key, char *value)
{
	if (!key || !value)
		return (0);
	if (ft_strcmp(key, "NO") == 0)
		return (set_texture(&var->tex.north, value));
	else if (ft_strcmp(key, "SO") == 0)
		return (set_texture(&var->tex.south, value));
	else if (ft_strcmp(key, "WE") == 0)
		return (set_texture(&var->tex.west, value));
	else if (ft_strcmp(key, "EA") == 0)
		return (set_texture(&var->tex.east, value));
	else if (ft_strcmp(key, "DO") == 0)
		return (set_texture(&var->tex.door, value));
	else if (ft_strcmp(key, "F") == 0)
		return (set_color(&var->floor, value));
	else if (ft_strcmp(key, "C") == 0)
		return (set_color(&var->sky, value));
	return (0);
}
