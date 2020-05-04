/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:27:32 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/29 17:51:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void     init_menu(t_env *env)
{
    SDL_Surface *tmp;

    if(TTF_Init() == -1)
    {
        printf("%s", TTF_GetError());
        exit(0);
    }
    //RECUPERATION DE MES IMAGES POUR LES MENUS
    if (!(env->menu.menu1 = SDL_LoadBMP("includes/assets/menus/Doom-menu.bmp")))
        ft_exit(env, "SDL_LoadBMP fail1", 0);

    if (!(env->menu.menu2 = SDL_LoadBMP("includes/assets/menus/Doom-pause.bmp")))
        ft_exit(env, "SDL_LoadBMP fail2", 0);

    if (!(env->menu.menu3 = SDL_LoadBMP("includes/assets/menus/Doom-settings.bmp")))
        ft_exit(env, "SDL_LoadBMP fail3", 0);
}

void            init_sdl(t_env *env)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
		ft_exit(env, "SDL_Init fail", 0);
    if (!(env->window = SDL_CreateWindow("DooM NukeM",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_W, W_H, 0)))
        ft_exit(env, "windows creation failed", 0);
    if (!(env->rend = SDL_CreateRenderer(env->window, -1, SDL_RENDERER_ACCELERATED)))
        ft_exit(env, "create renderer fail", 0);
    env->winsurf = SDL_CreateRGBSurface(0, W_W, W_H, 32, 0, 0, 0, 0);
    init_menu(env); 
    //SDL_ShowCursor(SDL_DISABLE);
}