/* ************************************************************************** */
/*                                                                            */
/*   doors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_email@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 10:00:00 by your_username    #+#    #+#             */
/*   Updated: 2025/09/21 10:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_door_at_position(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return (0);
	return (game->vars->map[y][x] == 'D' || game->vars->map[y][x] == 'd');
}

int	is_door_open(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return (0);
	return (game->vars->map[y][x] == 'd');
}

void	toggle_door(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->vars->map_w || y < 0 || y >= game->vars->map_h)
		return ;
	
	if (game->vars->map[y][x] == 'D')
	{
		game->vars->map[y][x] = 'd';  // Open the door
		printf("Door opened at (%d, %d)\n", x, y);
	}
	else if (game->vars->map[y][x] == 'd')
	{
		game->vars->map[y][x] = 'D';  // Close the door
		printf("Door closed at (%d, %d)\n", x, y);
	}
}

int find_nearest_door(t_game *game, int *door_x, int *door_y)
{
    double ray_x, ray_y;
    double step_x, step_y;
    int map_x, map_y;
    double max_distance = 2.0; // Maximum interaction distance
    
    // Cast a ray in the direction player is facing
    ray_x = game->player->posX;
    ray_y = game->player->posY;
    step_x = game->player->dir_x * 0.1;
    step_y = game->player->dir_y * 0.1;
    
    for (int i = 0; i < (int)(max_distance / 0.1); i++)
    {
        ray_x += step_x;
        ray_y += step_y;
        map_x = (int)ray_x;
        map_y = (int)ray_y;
        
        if (map_x >= 0 && map_x < game->vars->map_w && 
            map_y >= 0 && map_y < game->vars->map_h)
        {
            char cell = game->vars->map[map_y][map_x];
            if (cell == 'D' || cell == 'd')
            {
                *door_x = map_x;
                *door_y = map_y;
                return (1);
            }
            // Stop if we hit a wall
            if (cell == '1')
                break;
        }
    }
    return (0);
}

void handle_door_interaction(t_game *game)
{
    int door_x, door_y;
    
    if (find_nearest_door(game, &door_x, &door_y))
    {
        char current_state = game->vars->map[door_y][door_x];
        
        if (current_state == 'D')
        {
            game->vars->map[door_y][door_x] = 'd';
            printf("🚪 Door opened at (%d, %d)\n", door_x, door_y);
        }
        else if (current_state == 'd')
        {
            // Check if player would be trapped inside door
            if (!((int)game->player->posX == door_x && 
                  (int)game->player->posY == door_y))
            {
                game->vars->map[door_y][door_x] = 'D';
                printf("🚪 Door closed at (%d, %d)\n", door_x, door_y);
            }
            else
            {
                printf("❌ Cannot close door - you're standing in it!\n");
            }
        }
    }
    else
    {
        printf("❓ No door in front of you\n");
    }
}

// Modified DDA algorithm to handle doors
int	perform_dda_with_doors(t_game *game, t_ray_data *data)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->mapX += data->stepX;
			side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->mapY += data->stepY;
			side = 1;
		}
		
		if (data->mapX >= 0 && data->mapX < game->vars->map_w
			&& data->mapY >= 0 && data->mapY < game->vars->map_h)
		{
			char map_char = game->vars->map[data->mapY][data->mapX];
			// Hit wall
			if (map_char == '1')
				hit = 1;
			// Hit closed door
			else if (map_char == 'D')
				hit = 1;
			// Open door - continue raycast (treat as empty space)
			// map_char == 'd' - no hit, continue
		}
	}
	return (side);
}

// Modified raycast function for doors


// Modified texture selection to include doors
t_texture	*get_wall_texture_with_doors(t_game *game, t_ray *ray, double rayDirX, double rayDirY)
{
	char	map_char;
	
	if (ray->mapX >= 0 && ray->mapX < game->vars->map_w 
		&& ray->mapY >= 0 && ray->mapY < game->vars->map_h)
	{
		map_char = game->vars->map[ray->mapY][ray->mapX];
		
		// Return door texture for closed doors
		if (map_char == 'D')
			return (game->tex_door);
	}
	
	// Default wall texture selection
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

// Updated movement validation to handle doors
int	is_valid_move_with_doors(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;
	char	map_char;

	map_x = (int)new_x;
	map_y = (int)new_y;
	
	if (map_x < 0 || map_x >= game->vars->map_w
		|| map_y < 0 || map_y >= game->vars->map_h)
		return (0);
	
	map_char = game->vars->map[map_y][map_x];
	
	// Can't move through walls or closed doors
	if (map_char == '1' || map_char == 'D')
		return (0);
	
	// Can move through open doors and empty spaces
	return (1);
}

t_ray	cast_ray_with_doors(t_game *game, double rayDirX, double rayDirY)
{
	t_ray		ray;
	t_ray_data	data;
	int			side;

	init_ray_data(game, rayDirX, rayDirY, &data);
	calculate_step_x(game, rayDirX, &data);
	calculate_step_y(game, rayDirY, &data);
	side = perform_dda_with_doors(game, &data);  // Use door-aware DDA
	calculate_wall_distance(game, rayDirX, rayDirY, &data, &ray, side);
	ray.side = side;
	ray.mapX = data.mapX;
	ray.mapY = data.mapY;
	return (ray);
}