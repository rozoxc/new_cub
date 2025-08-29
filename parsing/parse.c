/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 01:21:15 by selbouka          #+#    #+#             */
/*   Updated: 2025/08/24 09:44:26 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int parser(char *file, t_game *game)
    {
     

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
        printf("Parsing successful!\n"); 
        return (1);
    }

// int main (int c , char **v)
// {
//     // printf ("%s\n", v[1]);
//     parser(v[1]);
// }