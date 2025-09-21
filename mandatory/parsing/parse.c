/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:21:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/09/21 08:24:29 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int parser(char *file, t_game *game)
{
    if (!file)
        return (write(2, "File path is empty ! [./cub3d FILE_PATH]", 41), 0);
    game->player = ft_malloc(sizeof(t_player), 1);
    if (!game->player)
        return (err("Allocation failed\n"), 0);
    game->player->dir_x = 0;
    game->player->dir_y = -1;
    game->vars = ft_malloc(sizeof(t_vars), 1);
    init_vars(game->vars);
    if (!validate_path_and_open(file, game->vars))
        return (0);
    if (!parse_header(game->vars))
    {
        close(game->vars->fd);
        return (0);
    }
    if (!parse_map(game))
    {
        close(game->vars->fd);
        return (0);
    }
    close(game->vars->fd); 
    return (1);
}
