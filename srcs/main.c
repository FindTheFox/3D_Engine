/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:06:03 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/02 21:03:24 by brpinto          ###   ########.fr       */
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
    int     i;
    int     mi;

    if (ac >= 2)
    {
		if (!ft_strcmp(av[1], "editor"))
		{
			printf("editor\n");
			init_editor(ac, env);
		}
		else
		{
			env->state = GAME;
        	env->nbmesh = ac - 1;
        	if (!(env->mesh = (t_mesh *)malloc(sizeof(t_mesh) * env->nbmesh)))
            	ft_exit(env, "Mesh Alloc Error", 0); 
        	i = 1;
        	mi = 0;
        	while (i < ac)
        	{
				env->mesh_id = mi;
				env->mesh[mi] = obj_parser(av[i], env);
          		env->mesh[mi].color = colorset(env, mi);
            	env->mesh[mi].name = av[i];
            	mi++;
            	i++;
        	}
		}
	}
    else
    {
		env->state = GAME;
        printf("cube init\n");
        env->nbmesh = 1;
        init_cube(env);
    }
    init_sdl(env);
    init_data(env);
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
		key_events(&env);
		if (env.state == GAME || env.state == FORGE)
			(env.usr.f[env.usr.platform])((void*)&env);
		ui_manager(&env);
	}
    return (0);
}

