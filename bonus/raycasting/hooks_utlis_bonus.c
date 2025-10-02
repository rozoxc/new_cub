/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utlis_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:32:57 by ababdoul          #+#    #+#             */
/*   Updated: 2025/10/02 07:49:45 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void update_door_system(t_game *game)
{
    static int space_cooldown = 0;
    
    if (space_cooldown > 0)
        space_cooldown--;

    if (game->keys->space && space_cooldown == 0)
    {
        handle_door_interaction(game);
        space_cooldown = 10;
    }
}

void	init_keys(t_game *game)
{
	game->keys = ft_malloc(sizeof(t_keys), 1);
	if (!game->keys)
		return ;
	game->keys->a = 0;
	game->keys->d = 0;
	game->keys->s = 0;
	game->keys->w = 0;
	game->keys->left = 0;
	game->keys->right = 0;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->mlx, game->win);
		ft_malloc (0, 0);
		exit(0);
	}
	else if (keycode == KEY_A)
		game->keys->a = 1;
	else if (keycode == KEY_D)
		game->keys->d = 1;
	else if (keycode == KEY_S)
		game->keys->s = 1;
	else if (keycode == KEY_W)
		game->keys->w = 1;
	else if (keycode == KEY_LEFT)
		game->keys->left = 1;
	else if (keycode == KEY_RIGHT)
		game->keys->right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys->w = 0;
	else if (keycode == KEY_S)
		game->keys->s = 0;
	else if (keycode == KEY_A)
		game->keys->a = 0;
	else if (keycode == KEY_D)
		game->keys->d = 0;
	else if (keycode == KEY_LEFT)
		game->keys->left = 0;
	else if (keycode == KEY_RIGHT)
		game->keys->right = 0;
	return (0);
}

int	close_window(void)
{
	exit(1);
	return (0);
}

int	is_valid_move(t_game *game, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= (int)game->vars->map_w
		|| map_y < 0 || map_y >= (int)game->vars->map_h)
		return (0);
	cell = game->vars->map[map_y][map_x];
	if (cell == '1' || cell == 'D')
		return (0);
	return (1);
}