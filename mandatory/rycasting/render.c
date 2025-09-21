/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 00:11:36 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/21 08:38:31 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


void render_game(t_game *game)
{
    render_3d(game);
    mlx_put_image_to_window(game->mlx, game->win, game->image->img, 0, 0);
}
