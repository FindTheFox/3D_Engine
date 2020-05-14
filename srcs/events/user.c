/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 23:54:42 by user42            #+#    #+#             */
/*   Updated: 2020/04/30 03:21:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        user_events(t_env *e)
{
    if (e->key[F1])
    {
        e->usr.forge = e->usr.forge == false ? true : false;
        e->key[F1] = 0;
    }
    else if (e->key[F2])
    {
        e->usr.fill_text = e->usr.fill_text == false ? true : false;
        e->key[F2] = 0;
    }    
    else if (e->key[F3])
    {
        e->usr.draw_line = e->usr.draw_line == false ? true : false;
        e->key[F3] = 0;
    }    
    else if (e->key[F4])
    {
        e->usr.mouse_motion = e->usr.mouse_motion == false ? true : false;
        e->key[F4] = 0;
    }    
    else if (e->key[F5])
    {
        e->usr.fps = e->usr.fps == false ? true : false;
        e->key[F5] = 0;
    }    
    if (e->key[F6])
    {
        e->usr.color = e->usr.color == false ? true : false;
        e->key[F6] = 0;
    }    
    /*
    **  Les touches F* libres
    */
/*
    if (e->key[F7]) 
        e->usr.mode = 0;
    if (e->key[F8])
        e->usr.mode = 0;
    if (e->key[F9])
        e->usr.mode = 0;
    if (e->key[F10])
        e->usr.mode = 0;
    if (e->key[F11])
        e->usr.mode = 0;
    if (e->key[F12])
        e->usr.mode = 0;

*/
}