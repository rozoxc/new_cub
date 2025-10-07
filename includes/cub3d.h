/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababdoul <ababdoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:27:20 by selbouka          #+#    #+#             */
/*   Updated: 2025/10/07 09:03:44 by ababdoul         ###   ########.fr       */
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
#include <stdbool.h>


// x = 100 out of 1000 width = 0.1 (10%)
// y = 447 out of 800 height = 0.55875 (55.875%)
#define WINDOW_WIDTH 1700
#define WINDOW_HEIGHT 1200
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
# define ROT_SPEED 0.1
# define MOVE_SPEED 0.1

#define MINI_MAP_HEIGHT 50
#define MINI_MAP_WIDHT 50


//<------------------------------>/
#define MINIMAP_SIZE 100       // Make bigger/smaller
#define MINIMAP_VIEW_RANGE 12   // Show more/less area around player
#define MINIMAP_TILE_SIZE 10   // Zoom in/out
#define MINIMAP_OFFSET_X 20     // Move minimap position
#define MINIMAP_OFFSET_Y 20

#define MINIMAP_DOOR_CLOSED_COLOR 0x8B4513    // Brown for closed doors
#define MINIMAP_DOOR_OPEN_COLOR 0x90EE90      // Light green for open doors
typedef struct s_render_data
{
	int				x;
	int				y;
	int				start_x;
	int				start_y;
	unsigned int	pixel_color;
	unsigned int	transparent_color;
	int				should_draw;
}	t_render_data;

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

#define MOUSE_SENSITIVITY 0.003
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
    int max_distance;
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
    int space;    // Add space key for door interaction
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

typedef struct s_door
{
    int x;
    int y;
    char state;           // 'D' = closed, 'd' = open, 'O' = opening, 'C' = closing
    float animation_progress; // 0.0 to 1.0
    int animation_frames;     // For smooth animation
} t_door;

typedef enum e_door_type
{
    DOOR_WOODEN,
    DOOR_METAL,
    DOOR_LOCKED,
    DOOR_AUTO     // Automatic doors that open when player approaches
} t_door_type;

// Advanced door management system
typedef struct s_door_manager
{
    t_door *doors;
    int door_count;
    int max_doors;
} t_door_manager;






// --------------------//

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
    int rgb;
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
	t_rgb		sky;
	char		**map;		
	size_t		map_h;	
	size_t		map_w;	
	int			fd;
	
}	t_vars;

typedef struct s_ray_calc
{
	double		ray_dirx;
	double		ray_diry;
	int			side;
	t_ray_data	*data;
	t_ray		*ray;
}	t_ray_calc;

typedef struct s_draw
{
	int				x;
	int				y;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	int				tex_y;
	int				line_height;
	double			step;
	double			tex_pos;
}	t_draw;

typedef struct s_render
{
    double camera_x;
    double ray_dirx;
    double ray_diry;
    t_texture *current_texture;
    int tex_x;
    t_ray ray;

}   t_render;

// Add to the key definitions section
#define KEY_SPACE 32     // Space key for door interaction

// Add to the t_keys structure (update your existing structure)


// Add to the t_game structure (add this member)
typedef struct  s_game
{
    void        *mlx;
    void        *win;
    t_texture  *tex_north;
    t_texture  *tex_south;
    t_texture  *tex_east;
    t_texture  *tex_west;
    t_texture  *tex_door;      // Add door texture
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
    t_vars      *vars;
    int weapon;
    int x_loop;
} t_game;


typedef struct s_map_reader
{
	char	**lines;
	size_t	capacity;
	size_t	*line_count;
	size_t	*max_width;
}	t_map_reader;

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
void	step_ray_x(t_ray_data *data, int *side);
void	step_ray_y(t_ray_data *data, int *side);
// static int		validate_map_walls(t_game *vars);
// static int	validate_map_walls(t_game *vars);
int	check_wall_hit(t_game *game, t_ray_data *data);

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


int	is_valid_move(t_game *game, double new_x, double new_y);

void	calculate_wall_bounds(t_ray *ray, int *drawStart, int *drawEnd);
void	calc_perp_wall_dist(t_game *game, t_ray_data *data,
		t_ray *ray, t_ray_calc *calc);
void	draw_sky(t_game *game);
void	draw_floor(t_game *game);
void	step_in_x(t_ray_data *data);
void	step_in_y(t_ray_data *data);

#define MAX_RAY_DISTANCE 50 


int		is_door_at_position(t_game *game, int x, int y);
int		is_door_open(t_game *game, int x, int y);
void	toggle_door(t_game *game, int x, int y);
void	handle_door_interaction(t_game *game);
int		perform_dda_with_doors(t_game *game, t_ray_data *data);
t_ray	cast_ray_with_doors(t_game *game, double rayDirX, double rayDirY);
t_texture	*get_wall_texture_with_doors(t_game *game, t_ray *ray, double rayDirX, double rayDirY);
int		is_valid_move_with_doors(t_game *game, double new_x, double new_y);
void	calc_wall_x(t_game *game, t_ray *ray, t_ray_calc *calc);
// DDA Algorithm functions
void    init_ray_data(t_game *game, double rayDirX, double rayDirY, t_ray_data *data);
void    calculate_step_x(t_game *game, double rayDirX, t_ray_data *data);
void    calculate_step_y(t_game *game, double rayDirY, t_ray_data *data);
int     perform_dda(t_game *game, t_ray_data *data);
// Door helper functions  
int     find_nearest_door(t_game *game, int *door_x, int *door_y);
void    update_door_system(t_game *game);
void rgb_to_mlx_color(t_rgb *rgb);




// utils

int	process_map_content(t_game *vars);
int	is_valid_map_char(char c);
int	is_player_char(char c);
int	create_padded_map(t_vars *vars, char **tmp_lines);
int	ft_only_ones(char *str);
int	ft_start_with_one(t_vars *vars);

void	rgb_to_mlx_color(t_rgb *rgb);
int	set_color(t_rgb *color, char *rgb);
int	set_item(t_vars *var, char *key, char *value);
int	set_texture(char **texture_ptr, char *path);
bool	firstarg(char *key);
char	**read_map_lines(t_vars *vars, size_t *line_count, size_t *max_width);
int	validate_path_and_open(char *path, t_vars *var);














// bns

int	is_valid_map_char(char c);

void	calculate_wall_distance_b(t_game *game, double rayDirX, double rayDirY,
	t_ray_data *data, t_ray *ray, int side);

// map process
void	init_player_direction(t_player *player, char dir);
int	ft_end_with_one(t_vars *vars);
int	ft_check_zero_surroundings(char **map, int i, int j, t_vars *vars);
int	is_player_char(char c);
char	**resize_and_copy(char **lines, size_t *capacity, size_t count);


int	process_line(char *line, char **lines, size_t *count, size_t *max);
char	**read_map_lines(t_vars *vars, size_t *line_count, \
	size_t *max_width);
int	create_padded_map(t_vars *vars, char **tmp_lines);
int	handle_player_position(t_game *vars, size_t x, size_t y, \
	int *player_count);


int	process_map_content(t_game *vars);
int	ft_only_ones(char *str);
int	ft_start_with_one(t_vars *vars);



// doors

int	is_door_open(t_game *game, int x, int y);
void	toggle_door(t_game *game, int x, int y);
int	check_door_in_ray(t_game *game, double *ray_x, double *ray_y,
	int *door_coords);
int	find_nearest_door(t_game *game, int *door_x, int *door_y);


int	is_door_at_position(t_game *game, int x, int y);
int	can_close_door(t_game *game, int door_x, int door_y);
void	handle_door_interaction(t_game *game);
t_texture	*select_wall_texture(t_game *game, t_ray *ray,
	double rayDirX, double rayDirY);


//bonus function utlis 

void	draw_minimap_player(t_game *game, int center_x, int center_y);
void	draw_minimap_tile(t_game *game, int screen_x, int screen_y, int color);
int	is_valid_map_tile(char tile);
void	draw_minimap_background(t_game *game);
void	draw_tile_by_type(t_game *game, char map_tile, int screen_x, int screen_y);
void	process_map_tile(t_game *game, t_minimap_data *mini, int map_x,
		int map_y);

typedef struct s_wall_draw
{
	int		drawStart;
	int		drawEnd;
	int		y;
	int		texY;
	double	step;
	double	texPos;
}	t_wall_draw;

typedef struct s_render_ray
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			texX;
	t_ray		ray;
	t_texture	*current_texture;
}	t_render_ray;

typedef struct s_wall_params
{
	t_ray		*ray;
	int			x;
	int			texX;
	t_texture	*texture;
}	t_wall_params;

void	init_ray_data_bonus(t_game *game, int x, t_render_ray *r);
void	init_wall_drawing(t_wall_draw *w, t_ray *ray, t_texture *texture);
int	calculate_tex_x(t_ray *ray, t_texture *texture, double rayDirX,
		double rayDirY);
void	rotate_player_mouse(t_game *game, double angle);
void	init_mouse_hook(int x, int *prev_x, int *initialized);
void	move_left_right(t_game *game, int direction);
void	move_forward_backward(t_game *game, int direction);
#endif