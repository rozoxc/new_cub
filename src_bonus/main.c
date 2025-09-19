/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:30:24 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/19 10:23:16 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_image *init_image(t_game *game)
{
    t_image *img;

    img = malloc(sizeof(t_image));
    if (!img)
        return NULL;
    img->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!img->img)
    {
        free(img);
        return NULL;
    }
    img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel, &img->len_lenght, &img->endian);
    return (img);
}

int main(int ac, char **av)
{
    t_game *game;
    game = malloc(sizeof(t_game));
    (void)ac;
    (void)av;

    if (!parser(av[1], game)) // kantsnaw selbouka 
        return(0);
    
    game->mlx = mlx_init();
    if (!game->mlx)
        return (1);
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!game->win)
        return (1);
    game->image = init_image(game);
    if (!game->image)
        return (1);
    if (!load_all_textures(game))
        return (0);
    init_keys(game);
    mlx_hook(game->win, 02, 1L<<0, key_press, game);
    mlx_hook(game->win, 03, 1L<<1, key_release, game);
    // mlx_hook(game->win, 17, 1L << 17, handle_close, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_hook(game->win, 6, 1L<<6, mouse_move_hook, game);
    mlx_loop(game->mlx);
    mlx_destroy_window(game->mlx, game->win);
}