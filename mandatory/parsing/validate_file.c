/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:24:50 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/03 17:29:09 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	ends(char *s, char *end)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
			break ;
		i++;
	}
	if (i == ft_strlen(s))
		return (false);
	else if (ft_strcmp(s + i, end) == 0)
		return (true);
	return (false);
}

int	validate_path_and_open(char *path, t_vars *var)
{
	if (ends(path, ".cub") == false)
		return (err("Path not valid\n"), 0);
	var->fd = open(path, O_RDONLY);
	if (var->fd < 0)
		return (err("File opening failed\n"), 0);
	return (1);
}
