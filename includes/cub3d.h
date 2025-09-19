/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selbouka <selbouka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:35:40 by ababdoul          #+#    #+#             */
/*   Updated: 2025/09/19 14:53:16 by selbouka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
# include <fcntl.h>
#include <math.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define MAP_WIDTH 28
#define MAP_HEIGHT 19
#define TITLE_SIZE 8
#define SPEED 5
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.05

#define MINI_MAP_HEIGHT 50
#define MINI_MAP_WIDHT 50


//<------------------------------>/
#define MINIMAP_SIZE 100       // Make bigger/smaller
#define MINIMAP_VIEW_RANGE 12   // Show more/less area around player
#define MINIMAP_TILE_SIZE 10   // Zoom in/out
#define MINIMAP_OFFSET_X 20     // Move minimap position
#define MINIMAP_OFFSET_Y 20

typedef struct s_line_data
{
	int	end_x;
	int	end_y;
	int	dx;
	int	dy;
	int	x;
	int	y;
	int	n;
	int	x_inc;
	int	y_inc;
	int	error;
}	t_line_data;

typedef struct s_minimap_data
{
	int	center_x;
	int	center_y;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_minimap_data;

#define MINIMAP_WALL_COLOR 0xFFFFFF      // White walls
#define MINIMAP_FLOOR_COLOR 0x333333     // Dark floor
#define MINIMAP_PLAYER_COLOR 0xFF0000    // Red player
#define MINIMAP_DIR_COLOR 0xFFFF00       // Yellow direction line
#define MINIMAP_BG_COLOR 0x000000        // Black background
//<----------------------------------->
#define ERROR_MAP "Error to load map\n"
#define ERROR_INIT "faild to initialize the game\n"

#define MOUSE_SENSITIVITY 0.001
typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_texture;

// typedef struct s_player{
//     double plan_x;
//     double plan_y;
//     double dir_x;
//     double dir_y;
//     double posX;
//     double posY;
// } t_player;

typedef struct s_image
{
    void *img;
    char *addr;
    int bit_per_pixel;
    int len_lenght;
    int endian;
} t_image;

typedef struct s_map
{
    char **map;
    int width;
    int height;   
}t_map;
typedef struct s_ray_data
{
    int     mapX;
    int     mapY;
    double  sideDistX;
    double  sideDistY;
    double  deltaDistX;
    double  deltaDistY;
    int     stepX;
    int     stepY;
}   t_ray_data;
typedef struct s_ray
{
    double perpWallDist;
    int side;
    int mapX;
    int mapY;
    double wallX;
} t_ray;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}t_keys;



// typedef struct  s_game
// {
//     void        *mlx;
//     void        *win;
//     t_texture  *texture;
//     t_player    *player;
//     t_map       *map;
//     t_image     *image;
//     t_keys      *keys;
//     int         height;
//     int         weight;
//     int         view_mode;
// } t_game;








// --------------------//

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;


typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*door;
    char    *Hands;
    char    *shoot0;
    char    *shoot1;

    
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
    
}	t_textures;


typedef struct s_player{
    double plan_x;
    double plan_y;
    double dir_x;
    double dir_y;
    double posX;
    double posY;
	char		player_dir;
} t_player;


typedef struct s_vars
{
	t_textures	tex;
	t_rgb		floor;
	t_rgb		ceiling;
	char		**map;		
	size_t		map_h;	
	size_t		map_w;	
	int			fd;
	
}	t_vars;



typedef struct  s_game
{
    void        *mlx;
    void        *win;
    t_texture  *tex_north;
    t_texture  *tex_south;
    t_texture  *tex_east;
    t_texture  *tex_west;
    t_texture   *hands_tex;
    t_texture   *shoot0_text;
    t_texture   *shoot1_text;

    
    t_player    *player;
    t_map       *map;
    t_image     *image;
    t_keys      *keys;
    int         height;
    int         weight;
    int         view_mode;
    t_vars      *vars; // Add vars to the game structure
    int weapon;
} t_game;

int			parser(char *file, t_game *game);
int validate_path_and_open(char *path, t_vars *var);
int parse_header(t_vars *var);
int is_valid_rgb(char *str);
int count_char(char *str, char c);
int is_whitespace_only(char *str);
void init_vars(t_vars *var);
void	err(char *error);
int parse_map(t_game *var);
int is_valid_map_char(char c);
int is_player_char(char c);


static int		validate_map_walls(t_game *vars);
static int	validate_map_walls(t_game *vars);


//------------------//


void     render_game(t_game *game);
void draw_rectangle(t_game *game, int start_x, int start_y, int color);
void draw_circle(t_game *game, int center_x, int center_y, int radius, int color);
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
int key_press(int keycode, t_game *game);
int close_window(void);
void render_3d(t_game *game);
void init_keys(t_game *game);
int key_release(int keycode, t_game *game);
void player_mouvement(t_game *game);
int game_loop(t_game *game);
t_ray cast_ray(t_game *game, double ray_dirX, double ray_dirY);
t_textures *load_texture(t_game *game, char *filename);
int mouse_hook(int x, int y, t_game *game);
void put_textures(t_game *game);
t_texture *get_wall_texture(t_game *game, t_ray *ray, double rayDirX, double rayDirY);
int load_all_textures(t_game *game);
int load_wall_texture(t_game *game, t_ray *ray, double rayDirX, double rayDirY);
// mlx function to replace
unsigned int get_texture_pixel(t_texture *texture, int x, int y);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
int mouse_hook(int x, int y, t_game *game);
int	mouse_move_hook(int x, int y, t_game *game);
int shoot(t_game *game);
void render_hand_with_transparency(t_texture *image, int start_x, int start_y, t_game *game);
#endif