/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurgali <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 15:50:46 by anurgali          #+#    #+#             */
/*   Updated: 2020/02/09 21:33:22 by anurgali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int init_window(t_display *display) //initializing the window
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // if couldn't initialize the window
	{
		ft_putendl("Error initializing SDL.\n"); //print error
		return 0;
	}
	// if not, display the window with the SDL function SDL_CreateWindow
	display->window = SDL_CreateWindow("WOLF3D", 
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								WINDOW_WIDTH,
								WINDOW_HEIGHT,
								SDL_WINDOW_BORDERLESS);
	//if couldn't open the window - error
	if (!display->window)
	{
		ft_putendl("Error creating SDL window.\n");
		return 0;
	}
	//create the Renderer with function SDL_CreateRenderer 
	display->renderer = SDL_CreateRenderer(display->window, -1, 0);
	//if couldn't - error
	if (!display->renderer) 
	{ 
		ft_putendl("Error creating SDL renderer.\n");
		return 0;
	}
	// Set the blend mode used for drawing operations 
	SDL_SetRenderDrawBlendMode(display->renderer, SDL_BLENDMODE_BLEND);
	return 1;
}

//function to kill the window
void destroy_window(t_display *display)
{
	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);
	SDL_Quit();
}

void process_input(t_game *g, t_player *player)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type){
		case SDL_QUIT: {
			g->is_game_running = 0;
			break;
		}
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_ESCAPE)
			g->is_game_running = 0;
			if (event.key.keysym.sym == SDLK_UP)
			player->walk_direction = +1;
			if (event.key.keysym.sym == SDLK_DOWN)
			player->walk_direction = -1;
			if (event.key.keysym.sym == SDLK_RIGHT)
			player->turn_direction = +1;
			if (event.key.keysym.sym == SDLK_LEFT)
			player->turn_direction = -1;
			break;
		}
		case SDL_KEYUP: 
		{
			if (event.key.keysym.sym == SDLK_UP)
			player->walk_direction = 0;
			if (event.key.keysym.sym == SDLK_DOWN)
			player->walk_direction = 0;
			if (event.key.keysym.sym == SDLK_RIGHT)
			player->turn_direction = 0;
			if (event.key.keysym.sym == SDLK_LEFT)
			player->turn_direction = 0;
			break;
		}
	}
}
//update game objects as a function of deltatime
void update(t_game *g, t_display *ticks, t_player *player, t_map *map, t_rays *rays){
	float delta_time;
	//waste some time untill we rach the target frame time
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks->ticks_last_frame + FRAME_TIME_LENGTH));
	delta_time = (SDL_GetTicks() - ticks->ticks_last_frame) / 1000.0f; //getting frame per second; delta time is a difference between current millisecinds to the last frame; 
	ticks->ticks_last_frame = SDL_GetTicks(); 

	move_player(delta_time, player, map);
	cast_all_rays(player, map, rays);
}

//render game objects, render map.
void render(t_display *display, t_game *g, t_map *map, t_player *player, t_rays *rays)
{
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
	SDL_RenderClear(display->renderer);
	//TODO:
	//render game objects
	render_map(display, *map);
	render_rays(display, player, rays);
	render_player(display, player);
	SDL_RenderPresent(display->renderer);
}
int main (int ac, char **av)
{
	t_game g;
	t_display display;
	t_player player;
	t_map map;
	t_rays *rays;


		if (ac == 2)
		{
			rays = (t_rays *)(malloc(sizeof(t_rays) * (NUM_RAYS)));
			g.is_game_running = init_window(&display);
			setup(&g, &player);
			count(av[1], &map );
			storage(av[1], &map);
			while (g.is_game_running)
			{
				process_input(&g, &player);
				update(&g,  &display, &player, &map, rays);
				render(&display, &g, &map, &player, rays);
			}
			destroy_window(&display);
		}
		else
		{
			printf("Gimme one file hommie");
		}
		
	return 0;
}