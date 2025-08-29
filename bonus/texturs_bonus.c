/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:53:42 by ababdoul          #+#    #+#             */
/*   Updated: 2025/07/13 02:20:17 by ababdoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture *load_texture(t_game *game, char *filename)
{
    t_texture *texture;
    
    texture = malloc(sizeof(t_texture));
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
