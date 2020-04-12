/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:27:32 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        init_sdl(t_env *env)
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
		ft_exit(env, "SDL_Init fail", 0);
    if (!(env->window = SDL_CreateWindow("saneveu cube3d",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_W, W_H, 0)))
        ft_exit(env, "windows creation failed", 0);
    if (!(env->rend = SDL_CreateRenderer(env->window, -1, SDL_RENDERER_ACCELERATED)))
        ft_exit(env, "create renderer fail", 0);
    env->winsurf = SDL_CreateRGBSurface(0, W_W, W_H, 32, 0, 0, 0, 0);    
    SDL_ShowCursor(SDL_DISABLE);

    //RECUPERATION DE MES IMAGES POUR LES MENUS
    env->tmp = SDL_LoadBMP("Doom.bmp");
    if (env->tmp == NULL)
        ft_exit(env, "SDL_LoadBMP fail", 0);
    env->menu1 = SDL_CreateTextureFromSurface(env->rend, env->tmp);
    SDL_FreeSurface(env->tmp);
    if (env->menu1 == NULL)
        ft_exit(env, "SDL_CreateTextureFromSurface fail", 0);

    env->tmp = SDL_LoadBMP("Doom-pause.bmp");
    if (env->tmp == NULL)
        ft_exit(env, "SDL_LoadBMP fail", 0);
    env->menu2 = SDL_CreateTextureFromSurface(env->rend, env->tmp);
    SDL_FreeSurface(env->tmp);
    if (env->menu2 == NULL)
        ft_exit(env, "SDL_CreateTextureFromSurface fail", 0);

    env->tmp = SDL_LoadBMP("Doom-settings.bmp");
    if (env->tmp == NULL)
        ft_exit(env, "SDL_LoadBMP fail", 0);
    env->menu3 = SDL_CreateTextureFromSurface(env->rend, env->tmp);
    SDL_FreeSurface(env->tmp);
    if (env->menu3 == NULL)
        ft_exit(env, "SDL_CreateTextureFromSurface fail", 0);
}