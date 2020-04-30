/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:47:17 by user42            #+#    #+#             */
/*   Updated: 2020/04/30 03:53:53 by user42           ###   ########.fr       */
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
    //printf("POS: %d\n", tri->screen_pos);
    if (pos < PX_NB && pos >= 0)
    {
        e->usr.event_i_mesh = e->pixel_buff[pos];
        printf("Selected mesh: %s\n", e->mesh[e->usr.event_i_mesh].name);
    }
}

void            dev_event(t_env *env)
{
    int     pos;

    if (env->usr.forge)
    {
        SDL_GetMouseState(&env->mouse.x, &env->mouse.y);
        pos = env->mouse.y * W_W + (env->mouse.x - 1);
        SDL_ShowCursor(1);
        if (env->key[LCLICK])
        {
            printf("MOUSE X: %d         MOUSE Y: %d\n", env->mouse.x, env->mouse.y);
            printf("COLOR: %x\n", get_color(env->winsurf, env->mouse.x, env->mouse.y));
            env->key[LCLICK] = 0;
        }
        if (env->key[RCLICK])
        {
            select_pointing_tri(env, pos);
            env->key[RCLICK] = 0;
        }
    }
    else
        SDL_ShowCursor(env->usr.mouse_ptr);
}