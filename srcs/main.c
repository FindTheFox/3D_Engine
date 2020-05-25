/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:59:44 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/25 17:23:08 by qbenaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static void     framerate(t_env *e)
{
    float           oldtime;
    int             fps;

    oldtime = e->time;
    e->time = SDL_GetTicks();
    e->theta = (e->time - oldtime) / 1000;
    fps = 1.0 / e->theta;
    if (e->usr.fps)
        printf("FPS: %d\n", fps);
    SDL_GetWindowPosition(e->window, &e->wx, &e->wy);
}

static void        setup(t_env *env, int ac, char **av)
{
	if (ac == 1)
	{
		//Menu
	}
	//Dev arguments
	if (ac == 2)
	{
		if (!ft_strcmp("game", av[1]))
		{
			env->usr.platform = GAME;
			init_game(env);
		}
		else if (!ft_strcmp("editor", av[1]))
			env->usr.platform = FORGE;
	}
	init_sdl(env);
	init_data(env);
	init_world(env);
}

int         main(int ac, char **av)
{
    t_env   env;

    ft_memset(&env, 0, sizeof(t_env));
    setup(&env, ac, av);
    env.end = 1;
    while (env.end)
    {
        framerate(&env);
        (env.usr.f[env.usr.platform])((void*)&env);
    }
    return (0);
}
