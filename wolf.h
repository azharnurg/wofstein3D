/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurgali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 22:42:58 by anurgali          #+#    #+#             */
/*   Updated: 2020/02/09 22:43:37 by anurgali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <stdio.h>
# include <unistd.h>
# include "include/SDL.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>


# define FALSE 0
# define TRUE 1

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 64
# define MAP_NUM_ROWS 19
# define MAP_NUM_COLS 20

# define MINIMAP_SCALE_FACTOR 0.3 

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 80))

# define NUM_RAYS WINDOW_WIDTH

# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)


typedef struct s_game
{
	int is_game_running;
	float x;
	float y;
	float width;
	
}				t_game;

typedef struct s_display
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int ticks_last_frame;
}				t_display;

typedef struct s_map
{
	int **map;
	int			x;
	int			y;
	int num_rows;
	int num_col;
	
}				t_map;
typedef struct s_rgb
{
	int r;
	int g;
	int b;
}			t_rgb;
typedef struct s_player
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction; // -1 for left, +1 for right
	int walk_direction; // -1 back, +1 forward
	float rotation_angle;
	float walk_speed;
	float turn_speed;

}				t_player;

typedef struct	s_count
{
	int			fd;
	int			i;
	char		*line;
	char		**split;
}				t_count;

typedef struct s_ray
{
	float ray_angle;
	float wall_hit_x;
	float wall_hit_y;
	float distance;
	int was_hit_vert;
	int was_hit_horz;
	int is_ray_facing_up;
	int is_ray_facing_down;
	int is_ray_facing_left;
	int is_ray_facing_right;
	int wall_hit_content;
}			t_rays;

void setup(t_game *g, t_player *player);
void render_map(t_display *display, t_map map);
void storage (char *av, t_map *map);
int		count(char *av, t_map *map);
void render_player(t_display *display, t_player *player);
void move_player(float delta_time, t_player *player, t_map *map);
void cast_all_rays(t_player *player, t_map *map, t_rays *rays);
int map_has_wall_at(float x, float y, t_map *map);
void render_rays(t_display *render, t_player *player, t_rays *rays);
#endif