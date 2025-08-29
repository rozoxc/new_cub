/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:41:47 by ababdoul          #+#    #+#             */
/*   Updated: 2025/08/22 08:13:02 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
void f()
{
    system("leaks cub3d");
}
char *map_data[] = {
    "1111111111111111111111111111",
    "1100000000000110000000000011",
    "1011110111110110111110111101",
    "1011111111110110111111111101",
    "1011110111110110111110111101",
    "1000000000000000000000000001",
    "1011110110111111110110111101",
    "1011110110111111110110111101",
    "1000000110000110000110000001",
    "1000000000000110000110000001",
    "1011110100100000000110111101",
    "1011110110100N01110110111101",
    "1000000110100000010110000001",
    "1000000110000000110110000001",
    "1011110110111111110110111101",
    "1011110110000000000110111101",
    "1000000110000110000110000001",
    "1011110110111111110110111101",
    "1111111111111111111111111111"
};
t_player *init_player(t_map *map)
{
    t_player *player;
    int i;
    int j;
    
    player = malloc(sizeof(t_player));
    if (!player)
        return (NULL);
    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            if (map->map[i][j] == 'N')
            {
                player->posX = j + 0.5;
                player->posY = i + 0.5;
                player->dir_x = 0;
                player->dir_y = -1;
                player->plan_x = 0.60;
                player->plan_y = 0;
                return (player);
            }
            j++;
        }
        i++;
    }
    return (player);
}

t_map  *init_map()
{
    t_map *map;
    int i;

    map = malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    map->map = malloc(sizeof(char *) * MAP_HEIGHT);
    if (!map->map)
        return (NULL);
    map->height = MAP_HEIGHT;
    map->width = MAP_WIDTH;
    i = 0;
    while (i < MAP_HEIGHT)
    {
        map->map[i] = map_data[i];
        i++;
    }
    return (map);
}
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
    // atexit(f);
    t_game game;

    (void)ac;
    (void)av;
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);
    game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
    if (!game.win)
        return (1);
    // if (!parse(game)) // kantsnaw selbouka 
    //     return(0);
    game.image = init_image(&game);
    if (!game.image)
        return (1);
    game.map = init_map();
    if (!game.map)
        return (1); 
    game.player = init_player(game.map);
    if (!game.player)
        return (1);
    // game.view_mode = 0;
    game.texture = load_texture(&game, "/mnt/homes/ababdoul/Desktop/Cub3d/textures/eagle.xpm");
    if (!game.texture)
        printf("warning !!\n");
    init_keys(&game);
    mlx_hook(game.win, 02, 1L<<0, key_press, &game);
    mlx_hook(game.win, 03, 1L<<1, key_release, &game);
    // mlx_hook(game.win, 6, 1L<<6, mouse_hook, &game); // should fix it
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);

    // mlx_destroy_window(game.mlx, game.win);
}
