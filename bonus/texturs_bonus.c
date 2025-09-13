/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturs_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/13 22:53:34 by ababdoul         ###   ########.fr       */
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

    texture  = malloc(sizeof(texture));
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
    
    printf("Loaded texture: %s (%dx%d)\n", filename, texture->width, texture->height);
    return (texture);
}

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
    return (1);
}

// Get the correct texture filename based on wall direction and ray side
t_texture *get_wall_texture(t_game *game, t_ray *ray, double rayDirX, double rayDirY)
{
    if (ray->side == 0)
    {
        if (rayDirX > 0)
            return (game->tex_west);
        else
            return (game->tex_east);
    }
    else
    {
        if (rayDirY > 0)
            return (game->tex_north);
        else
            return (game->tex_south);
    }
}
