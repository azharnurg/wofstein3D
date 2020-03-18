/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurgali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:46:56 by anurgali          #+#    #+#             */
/*   Updated: 2020/02/21 18:47:10 by anurgali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
/*const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};*/

void setup(t_game *g, t_player *player)
{
		player->x = WINDOW_WIDTH / 2; //defining position of player by x
		player->y = WINDOW_HEIGHT / 2; //defining position of player by y
		player->width = 32; //defining width of player
		player->height = 32; //defining heght of player
		player->turn_direction = 0; // starting turn direction from 0
		player->walk_direction = 0; //starting walk direction from 0
		player->walk_speed  = PI / 2; //speed of walk
		player->walk_speed = 100; 
		player->turn_speed = 45 * (PI / 180); // turn speed

}

/*/moving a player
//perform wall collision
void move_player(float delta_time, t_player *player, t_map *map)
{
		float move_step;
		float new_player_x;
		float new_player_y;

		player->rotation_angle += player->turn_direction * player->turn_speed * delta_time;
		move_step = player->walk_direction * player->walk_speed * delta_time;
		new_player_x = player->x + cos(player->rotation_angle) * move_step;
		new_player_y = player->y + sin(player->rotation_angle) * move_step;
		
		if (!map_has_wall_at(new_player_x, new_player_y, map))
		{
			player->x = new_player_x;
			player->y = new_player_y;
		}
		else
		{
			printf("I hit the wall");
		}
		
		
		//TODO:
		//perform wall collision
}

//function which draws a
void render_player(t_display *display, t_player *player)
{
	SDL_SetRenderDrawColor(display->renderer, 255, 255, 255, 255);
	SDL_Rect player_rect = {
		player->x * MINIMAP_SCALE_FACTOR,
		player->y * MINIMAP_SCALE_FACTOR,
		player->width * MINIMAP_SCALE_FACTOR, 
		player->height * MINIMAP_SCALE_FACTOR
	};
	SDL_RenderFillRect(display->renderer, &player_rect);

	SDL_RenderDrawLine(
		display->renderer,
		MINIMAP_SCALE_FACTOR * player->x,
		MINIMAP_SCALE_FACTOR *	player->y, 
		MINIMAP_SCALE_FACTOR *	player->x + cos(player->rotation_angle) * 40,
		MINIMAP_SCALE_FACTOR *	player->y + sin(player->rotation_angle) * 40
	);
}*/

int				count(char *av, t_map *map)
{
	t_count		cnt;

	map->x = 0;
	map->y = 0;
	cnt.fd = open(av, O_RDONLY);
	while (ft_get_next_line(cnt.fd, &cnt.line) > 0)
	{
		map->y++;
		cnt.i = 0;
		cnt.split = ft_strsplit(cnt.line, ' ');
		while (cnt.split[cnt.i])
			cnt.i++;
		if (map->x == 0)
			map->x = cnt.i;
		else if (cnt.i != map->x)
			ft_putendl("Error: width didn't match");
	}
	printf("MAP x- %d, y- %d\n", map->x, map->y);
	close(cnt.fd);
	return (1);
}

void storage (char *av, t_map *map)
{
    int fd;
    char *line;
    char **split;
    int i;
    int j;

    i = 0;
    j = 0;
    fd = open (av, O_RDONLY);
    map->map = (int **)malloc(sizeof(int *) * (map->y));
    i = 0;
    while (ft_get_next_line(fd, &line) > 0)
    {
        map->map[i] = (int *)malloc(sizeof(int) * (map->x));
        split = ft_strsplit(line, ' ');
        j = 0;
        while (split[j])
        {
            map->map[i][j] = ft_atoi(split[j]);
            j++;
        }
		i++;
    }
	printf("Stored map\n");
	i = 0;
	j = 0;
	while (i < map->y )
	{
		j = 0;
		while(j < map->x)
		{
			printf("%d ", map->map[i][j]);
			j++;
		}
		printf("\n");
	i++;
	}
    close (fd);
}

void color_change(int map_value, t_rgb *color)
{
	if (map_value == 0)
	{
		color->r = 0;
		color->g = 0;
		color->b = 0;
	}
	else if (map_value == 1)
	{
		color->r = 255;
		color->g = 255;
		color->b = 255;
	}
	
}

void render_map(t_display *display, t_map map)
{
	int i;
	int j;
	int tile_x;
	int tile_y;
	t_rgb color;

	i = 0;
	while (i < map.y)
	{
		j = 0;
		while (j < map.x)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			color_change(map.map[i][j], &color);
			
			SDL_SetRenderDrawColor(display->renderer, color.r, color.g, color.b, 255);
				SDL_Rect map_tile_rect = {
					tile_x * MINIMAP_SCALE_FACTOR, 
					tile_y * MINIMAP_SCALE_FACTOR, 
					TILE_SIZE * MINIMAP_SCALE_FACTOR, 
					TILE_SIZE * MINIMAP_SCALE_FACTOR }; //* MINIMAP_SCALE_FACTOR,};
			SDL_RenderFillRect(display->renderer, &map_tile_rect);
			j++;
		}
		i++;
	}
}
