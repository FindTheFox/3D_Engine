/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_platform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:43:32 by user42            #+#    #+#             */
/*   Updated: 2020/05/18 12:25:53 by qbenaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void                menu_start(void *env)
{
    t_env *e;

    e = (t_env *)env;
    
}

void                menu_pause(void *env)
{
    t_env *e;

    e = (t_env *)env;

}

void                menu_option(void *env)
{
    t_env *e;

    e = (t_env *)env;

}

void                forge(void *env)
{
    t_env *e;

    e = (t_env *)env;
    reset_pbuffer(e);
    event(e);
    engine_3d(e);
    clear_dyntab(&e->to_raster); //test remove arr after do events for find triangle data
    sdl_render(env);
}

void                gameplay(void *env)
{
    t_env *e;

    e = (t_env *)env;
    reset_pbuffer(e);
    event(e);
	game_loop(e);
    engine_3d(e);
    clear_dyntab(&e->to_raster); //test remove arr after do events for find triangle data
    sdl_render(env);
}
