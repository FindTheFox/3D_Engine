/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_partform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 22:43:32 by user42            #+#    #+#             */
/*   Updated: 2020/04/28 22:55:59 by user42           ###   ########.fr       */
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
}

void                gameplay(void *env)
{
    t_env *e;

    e = (t_env *)env;
    reset_pbuffer(e);
    engine_3d(e);
    sdl_render(env);
}