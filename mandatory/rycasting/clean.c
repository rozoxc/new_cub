/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:57:38 by ababdoul          #+#    #+#             */
/*   Updated: 2025/11/01 18:33:14 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cleanup_textures(t_game *game)
{
	if (game->tex_north)
	{
		if (game->tex_north->img)
			mlx_destroy_image(game->mlx, game->tex_north->img);
	}
	if (game->tex_south)
	{
		if (game->tex_south->img)
			mlx_destroy_image(game->mlx, game->tex_south->img);
	}
	if (game->tex_east)
	{
		if (game->tex_east->img)
			mlx_destroy_image(game->mlx, game->tex_east->img);
	}
	if (game->tex_west)
	{
		if (game->tex_west->img)
			mlx_destroy_image(game->mlx, game->tex_west->img);
	}
}

void	cleanup_mlx(t_game *game)
{
	if (game->image)
	{
		if (game->image->img)
			mlx_destroy_image(game->mlx, game->image->img);
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	cleanup_textures(game);
	cleanup_mlx(game);
}
