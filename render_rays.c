/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurgali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:12:34 by anurgali          #+#    #+#             */
/*   Updated: 2020/03/05 12:12:42 by anurgali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


float distance_bw_points(float x1, float y1, float x2, float y2)
{
	return(sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1)));
}
float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return angle;
}

void cast_ray(float ray_angle, int strip_id, t_player *player, t_map *map, t_rays *rays)
{
	//all the crazy logics for horz, vert..
	ray_angle = normalize_angle(ray_angle);
	int is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	int is_ray_facing_up = !is_ray_facing_down;

	int is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int is_ray_facing_left = !is_ray_facing_right;

	float xintercept, yintercept;
    float xstep, ystep;

	float x_to_check;
	float y_to_check;


        ///////////////////////////////////////////
        // HORIZONTAL RAY-GRID INTERSECTION CODE
        ///////////////////////////////////////////
        int foundHorzWallHit = FALSE;
        float horzWallHitX = 0;
        float horzWallHitY = 0;
        int horzWallContent = 0;

        // Find the y-coordinate of the closest horizontal grid intersenction
        yintercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
        yintercept += is_ray_facing_down ? TILE_SIZE : 0;

        // Find the x-coordinate of the closest horizontal grid intersection
        xintercept = player->x + (yintercept - player->y) / tan(ray_angle);

        // Calculate the increment xstep and ystep
        ystep = TILE_SIZE;
        ystep *=is_ray_facing_up ? -1 : 1;

        xstep = TILE_SIZE / tan(ray_angle);
        xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
        xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

        float next_horz_touch_x = xintercept;
        float next_horz_touch_y = yintercept;

        // Increment xstep and ystep until we find a wall
        while (next_horz_touch_x >= 0 && next_horz_touch_x <= WINDOW_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WINDOW_HEIGHT) {
             x_to_check = next_horz_touch_x;
			 y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);
			
			if (map_has_wall_at(x_to_check, y_to_check, map)) 
			{
				// there is a wall hit
				horzWallHitX = next_horz_touch_x;
				horzWallHitY = next_horz_touch_y;
				horzWallContent = map->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
				foundHorzWallHit = TRUE; 
				break;
			}
			else
			{
				next_horz_touch_x += xstep;
				next_horz_touch_y += ystep;
			}
		}

		///////////////////////////////////////////
        // Vertical RAY-GRID INTERSECTION CODE
        ///////////////////////////////////////////
        int foundvertWallHit = FALSE;
        float vertWallHitX = 0;
        float vertWallHitY = 0;
        int vertWallContent = 0;

        // Find the x-coordinate of the closest horizontal grid intersenction
        xintercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
        xintercept += is_ray_facing_right ? TILE_SIZE : 0;

        // Find the y-coordinate of the closest horizontal grid intersection
        yintercept = player->y + (xintercept - player->x) * tan(ray_angle);

        // Calculate the increment xstep and ystep
        xstep = TILE_SIZE;
        xstep *=is_ray_facing_left ? -1 : 1;

        ystep = TILE_SIZE * tan(ray_angle);
        ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
        ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

        float next_vert_touch_x = xintercept;
        float next_vert_touch_y = yintercept;

		int wallnum = 0;
        // Increment xstep and ystep until we find a wall
        while (next_vert_touch_x >= 0 && next_vert_touch_x < WINDOW_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y < WINDOW_HEIGHT) {
             x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
			 y_to_check = next_vert_touch_y;
			//printf("VertTouch Y = %f < %d\n", next_vert_touch_y, WINDOW_HEIGHT);
			if (map_has_wall_at(x_to_check, y_to_check, map)) 
			{
				//printf("Map has Wall x\n");
				// there is a wall hit
				vertWallHitX = next_vert_touch_x;
				vertWallHitY = next_vert_touch_y;
				vertWallContent = map->map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
				foundvertWallHit = TRUE; 
				break;
			}
			else
			{
				next_vert_touch_x += xstep;
				next_vert_touch_y += ystep;
			}
		}
		// calculate oth horizontal and vertical hit distances and choose the smallest one
		float horz_hit_distance = foundHorzWallHit ? distance_bw_points(player->x, player->y, horzWallHitX, horzWallHitY) : INT_MAX;
		float vert_hit_distance = foundvertWallHit ? distance_bw_points(player->x, player->y, vertWallHitX, vertWallHitY) : INT_MAX;

		if (vert_hit_distance < horz_hit_distance)
		{
			rays[strip_id].distance = vert_hit_distance;
			rays[strip_id].wall_hit_x = vertWallHitX;
			rays[strip_id].wall_hit_y = vertWallHitY;
			rays[strip_id].wall_hit_content = vertWallContent;
			rays[strip_id].was_hit_vert  = TRUE;
		}
		else
		{
			rays[strip_id].distance = horz_hit_distance;
			rays[strip_id].wall_hit_x = horzWallHitX;
			rays[strip_id].wall_hit_y = horzWallHitY;
			rays[strip_id].wall_hit_content = horzWallContent;
			rays[strip_id].was_hit_horz  = TRUE;
		}
		rays[strip_id].ray_angle = ray_angle;
		rays[strip_id].is_ray_facing_down = is_ray_facing_down;
		rays[strip_id].is_ray_facing_up = is_ray_facing_up;
		rays[strip_id].is_ray_facing_right = is_ray_facing_right;
		rays[strip_id].is_ray_facing_left = is_ray_facing_left;
}
void cast_all_rays(t_player *player, t_map *map, t_rays *rays)
{
	float ray_angle;
	int strip_id;
	//start first ray substractiing half og our FOV
	ray_angle = player->rotation_angle - (FOV_ANGLE / 2);

	strip_id = 0;
	while(strip_id < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_id, player, map, rays);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
}

void render_rays(t_display *render, t_player *player, t_rays *rays)
{
    SDL_SetRenderDrawColor(render->renderer, 255, 0, 0, 255);
    for (int i = 0; i < NUM_RAYS; i++)
    {
        SDL_RenderDrawLine(render->renderer, MINIMAP_SCALE_FACTOR * player->x, MINIMAP_SCALE_FACTOR * player->y, MINIMAP_SCALE_FACTOR * rays[i].wall_hit_x, MINIMAP_SCALE_FACTOR * rays[i].wall_hit_y);
    }
}