/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:47:17 by user42            #+#    #+#             */
/*   Updated: 2020/05/04 01:35:19 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            select_pointing_tri(t_env *e, int pos)
{
    int x;
    int y;
    t_triangle *tri;
    
    if (!(tri = (t_triangle*)dyaddress(&e->to_raster, y)))
        ft_exit(e, "DooM: Fail dynarr tri load\nsrcs/event/dev_events.c\n", 0);
    if (pos < PX_NB && pos >= 0)
    {
        e->usr.select_mesh = e->depth_buff[pos].mesh_id;
        printf("Selected mesh: %s\n", e->mesh[e->usr.select_mesh].name);
    }
}

void            dev_event(t_env *env)
{
    int     pos;

    if (env->usr.forge)
    {
        SDL_GetMouseState(&env->mouse.x, &env->mouse.y);
        SDL_GetRelativeMouseState(&env->mouse.xrel, &env->mouse.yrel);
        pos = env->mouse.y * W_W + (env->mouse.x - 1);
        SDL_ShowCursor(1);
        if (env->key[LCLICK])
        {
            //printf("MOUSE X: %d         MOUSE Y: %d\n", env->mouse.x, env->mouse.y);
            printf("SCREENCOLOR: %x\n", get_color(env->winsurf, env->mouse.x, env->mouse.y));
            printf("TRI_COLOR:  %x\n", env->depth_buff[pos].color);
            printf("BUFF.W: %f\n\n", env->depth_buff[pos].w);
            //printf("TRI_ID: %d\n", env->depth_buff[pos].tri_id);
            
            env->key[LCLICK] = 0;
        }
        if (env->key[RCLICK])
        {
            select_pointing_tri(env, pos);
            env->key[RCLICK] = 0;
        }
    }
}