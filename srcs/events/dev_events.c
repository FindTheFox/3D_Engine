/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:47:17 by user42            #+#    #+#             */
/*   Updated: 2020/05/07 21:33:31 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            select_pointing_tri(t_env *e, int pos)
{
    int     x;
    int     y;
    t_mesh  *obj;
    
    if (pos < PX_NB && pos >= 0)
    {
        e->usr.select_mesh = e->depth_buff[pos].mesh_id;
        obj = (t_mesh *)ft_listfind(&e->world_obj, e->usr.select_mesh);
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf("Selected mesh: %s\n", obj->name);
        printf("meshid: %d\n", e->usr.select_mesh);
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    }
}

void            dev_event(t_env *env)
{
    int         pos;
    t_mesh      *obj;

    obj = NULL;
    if (env->usr.forge)
    {
        SDL_GetMouseState(&env->mouse.x, &env->mouse.y);
        SDL_GetRelativeMouseState(&env->mouse.xrel, &env->mouse.yrel);
        pos = env->mouse.y * W_W + (env->mouse.x - 1);
        SDL_ShowCursor(1);
        if (env->key[LCLICK])
        {
            //printf("MOUSE X: %d         MOUSE Y: %d\n", env->mouse.x, env->mouse.y);
            //printf("SCREENCOLOR: %x\n", get_color(env->winsurf, env->mouse.x, env->mouse.y));
            //printf("TRI_COLOR:  %x\n", env->depth_buff[pos].color);
            //printf("BUFF.W: %f\n\n", env->depth_buff[pos].w);
            //printf("TRI_ID: %d\n", env->depth_buff[pos].tri_id);
            if(!(obj = (t_mesh*)ft_listfind(&env->world_obj, env->usr.select_mesh)))
                ft_exit(env, "DooM: Drag_and_Drop failed\n", 0);
            //select_pointing_tri(env, pos);            
            drag_and_drop(env, obj, env->mouse.xrel, env->mouse.yrel);
        }
        if (env->key[RCLICK])
        {
            select_pointing_tri(env, pos);
            env->key[RCLICK] = 0;
        }
        else if (env->key[DEL])
        {
            remove_obj(env, env->usr.select_mesh);
            env->key[DEL] = 0;
        }
        else if (env->key[INSERT])
        {
            obj = &env->mesh[env->usr.new_obj];
            pop_obj(env, obj);
            env->key[INSERT] = 0;
        }
        else if (env->key[PAGEUP])
        {
            select_save_obj(env, ++env->usr.new_obj);
            env->key[PAGEUP] = 0;
        }
        else if (env->key[PAGEDOWN])
        {
            env->usr.new_obj = env->usr.new_obj == 0 ? 0 : --env->usr.new_obj;
            select_save_obj(env, env->usr.new_obj);
            env->key[PAGEDOWN] = 0;
        }
    }
}