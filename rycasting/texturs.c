/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/08/26 22:00:41 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int get_texture_pixel(t_textures *texture, int x, int y)
{
    char *dst;
    
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    
    dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return (*(unsigned int*)dst);
}

t_textures *load_texture(t_game *game, char *filename)
{
    t_textures *texture;
    
    texture = malloc(sizeof(t_textures));
    if (!texture)
        return (NULL);
    
    texture->img = mlx_xpm_file_to_image(game->mlx, filename, 
                                       &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error: Could not load texture file %s\n", filename);
        free(texture);
        return (NULL);
    }
    
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                    &texture->line_length, &texture->endian);
    
    printf("Loaded texture: %s (%dx%d)\n", filename, texture->width, texture->height);
    return (texture);
}
void put_textures(t_game *game)
{
    if (game->player->player_dir == 'N')
        game->texture = load_texture(game, game->vars->tex.north);
    else if (game->player->player_dir == 'E')
        game->texture = load_texture(game, game->vars->tex.east);
    else if (game->player->player_dir == 'W')
        game->texture = load_texture(game, game->vars->tex.west);
    else if (game->player->player_dir == 'S')
        game->texture = load_texture(game, game->vars->tex.south);
}