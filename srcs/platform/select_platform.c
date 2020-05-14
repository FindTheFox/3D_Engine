/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_platform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:43:32 by user42            #+#    #+#             */
/*   Updated: 2020/04/29 21:07:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void                menu_start(void *env)
{
    t_env *e;

    e = (t_env *)env;
    main_menu(e);
    event_MainMenu(env);
    sdl_render(env);
}

void                menu_pause(void *env)
{
    t_env *e;

    e = (t_env *)env;
    pause_menu(e);
    event_MainMenu(env);
    sdl_render(env);
}

void                menu_option(void *env)
{
    t_env *e;

    e = (t_env *)env;
    //menu(e, CONTROLS_MENU);
    //sdl_render(env);
}

void                forge(void *env)
{
    t_env *e;

    e = (t_env *)env;
}

void                gameplay(void *env)
{
    t_env *e;

    e = (t_env *)env;
    reset_pbuffer(e);
    engine_3d(e);
    event(e);
    clear_dynarray(&e->to_raster); //test remove arr after do events for find triangle data
    sdl_render(env);
}