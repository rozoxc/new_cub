/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:38:20 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/13 22:16:38 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void init_keys(t_game * game)
{
    game->keys = malloc(sizeof(t_keys));
    if (!game->keys)
        return ;
    game->keys->a = 0;
    game->keys->d = 0;
    game->keys->s = 0;
    game->keys->w = 0;
    game->keys->left = 0;
    game->keys->right = 0;
}
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    else if (keycode == KEY_A)
        game->keys->a = 1;
    else if(keycode == KEY_D)
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
int key_release(int keycode, t_game *game)
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
int	is_valid_move(t_game *game, double new_x, double new_y)
{
	if (new_x >= 0 && new_x < game->vars->map_w
		&& new_y >= 0 && new_y < game->vars->map_h
		&& game->vars->map[(int)new_y][(int)new_x] != '1')
		return (1);
	return (0);
}

void	move_forward_backward(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	// printf("dirx: %.2f, diry: %.2f\n", game->player->dir_x, game->player->dir_y);
	new_x = game->player->posX + (direction * game->player->dir_x * MOVE_SPEED);
	new_y = game->player->posY + (direction * game->player->dir_y * MOVE_SPEED);
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}

void	move_left_right(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player->posX + (direction * game->player->plan_x * MOVE_SPEED);
	new_y = game->player->posY + (direction * game->player->plan_y * MOVE_SPEED);
	if (is_valid_move(game, new_x, new_y))
	{
		game->player->posX = new_x;
		game->player->posY = new_y;
	}
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plan_x;

	old_dir_x = game->player->dir_x;
	game->player->dir_x = game->player->dir_x * cos(angle)
		- game->player->dir_y * sin(angle);
	game->player->dir_y = old_dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	old_plan_x = game->player->plan_x;
	game->player->plan_x = game->player->plan_x * cos(angle)
		- game->player->plan_y * sin(angle);
	game->player->plan_y = old_plan_x * sin(angle)
		+ game->player->plan_y * cos(angle);
}

void	player_mouvement(t_game *game)
{
	// printf("Player Position: X: %.2f, Y: %.2f\n", game->player->posX, game->player->posY);
	if (game->keys->w)
		move_forward_backward(game, 1);
	else if (game->keys->s)
		move_forward_backward(game, -1);
	else if (game->keys->a)
		move_left_right(game, -1);
	else if (game->keys->d)
		move_left_right(game, 1);
	else if (game->keys->right)
		rotate_player(game, ROT_SPEED);
	else if (game->keys->left)
		rotate_player(game, -ROT_SPEED);
}

int game_loop(t_game *game)
{
    player_mouvement(game);
    render_game(game);
    return (0);
}
int close_window()
{
    exit(1);
    return (0);
}
