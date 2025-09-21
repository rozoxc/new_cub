/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturs_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/21 09:27:40 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int get_texture_pixel(t_texture *texture, int x, int y)
{
    char *dst;
    
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    
    dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

t_texture *load_single_texture(t_game *game, char *filename)
{
    t_texture *texture;

    texture  = ft_malloc(sizeof(*texture), 1);
    if (!texture)
        return (NULL);
    texture->img = mlx_xpm_file_to_image(game->mlx, filename, &texture->width, &texture->height);
    if (!texture->img)
    {
        perror("faild to load image!!\n");
        free(texture);
        return (NULL);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                    &texture->line_length, &texture->endian);
    return (texture);
}

/* Updated functions for texturs_bonus.c */

int load_all_textures(t_game *game)
{
    game->tex_north = load_single_texture(game, game->vars->tex.north);
    if (!game->tex_north)
        return (0);
    game->tex_east = load_single_texture(game, game->vars->tex.east);
    if (!game->tex_east)
        return (0);
    game->tex_south = load_single_texture(game, game->vars->tex.south);
    if (!game->tex_south)
        return (0);
    game->tex_west = load_single_texture(game, game->vars->tex.west);
    if (!game->tex_west)
        return (0);
    
    // Load door texture
    game->tex_door = load_single_texture(game, game->vars->tex.door);
    if (!game->tex_door)
        return (0);
    
    game->hands_tex = load_single_texture(game, game->vars->tex.Hands);
    if (!game->hands_tex)
        return (0);
    game->shoot0_text = load_single_texture(game, game->vars->tex.shoot0);
    if (!game->shoot0_text)
        return (0);
    game->shoot1_text = load_single_texture(game, game->vars->tex.shoot1);
    if (!game->shoot1_text)
        return (0);
    return (1);
}

// Replace the old get_wall_texture function with this one
t_texture *get_wall_texture(t_game *game, t_ray *ray, double rayDirX, double rayDirY)
{
    return get_wall_texture_with_doors(game, ray, rayDirX, rayDirY);
}

// t_texture *get_wall_texture(t_game *game, t_ray *ray, double rayDirX, double rayDirY)
// {
//     if (ray->side == 0)
//     {
//         if (rayDirX > 0)
//             return (game->tex_west);
//         else
//             return (game->tex_east);
//     }
//     else
//     {
//         if (rayDirY > 0)
//             return (game->tex_north);
//         else
//             return (game->tex_south);
//     }
// }
