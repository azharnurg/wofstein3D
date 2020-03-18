/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurgali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:49:54 by anurgali          #+#    #+#             */
/*   Updated: 2020/03/02 15:16:01 by anurgali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"

int map_has_wall_at(float x, float y, t_map *map)
{
	int map_grid_index_x;
	int map_grid_index_y;
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT){
		return 1;
	}
		map_grid_index_x = floor(x / TILE_SIZE);
		map_grid_index_y = floor(y / TILE_SIZE);

		//printf("Y = [%f] / 64 = %f\n", y, (y / TILE_SIZE));
		//printf("Map[%d][%d]\n", map_grid_index_y,map_grid_index_x);
	return (map->map[map_grid_index_y][map_grid_index_x] != 0);
}
//moving a player
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
}