/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:41:47 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/24 05:04:56 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_image	*init_image(t_game *game)
{
	t_image	*img;

	img = ft_malloc(sizeof(t_image), 1);
	if (!img)
		return (NULL);
	img->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!img->img)
		return (NULL);
	img->addr = mlx_get_data_addr(img->img, &img->bit_per_pixel,
			&img->len_lenght, &img->endian);
	return (img);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = ft_malloc(sizeof(t_game), 1);
	(void)ac;
	if (!parser(av[1], game))
		return (ft_malloc(0, 0), 0);
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
	mlx_hook(game->win, 02, 1L << 0, key_press, game);
	mlx_hook(game->win, 03, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
	ft_malloc(0, 0);
	mlx_destroy_window(game->mlx, game->win);
}
