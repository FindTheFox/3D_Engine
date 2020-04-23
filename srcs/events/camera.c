/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 16:03:00 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/26 19:17:36 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void                camera_rot_mouse_calc(t_env *e)
{
    int     midx;
    int     midy;
    int     xrel;
    int     yrel;

    midx = W_W / 2;
    midy = W_H / 2;
    xrel = (e->mouse.xrel);
    yrel = (e->mouse.yrel);
    if (xrel > midx && yrel >= midy)
    {
        e->yaw -= xrel * e->theta;;
        e->xaw -= yrel * e->theta;;
    }
    else if (xrel < midx && yrel >= midy)
    { 
        e->yaw += xrel * e->theta;
        e->xaw -= yrel * e->theta;
    }
    else if (xrel >= midx && yrel < midy)
    { 
        e->yaw -= xrel * e->theta;
        e->xaw += yrel * e->theta;
    }
    else if (xrel <= midx && yrel < midy)
    { 
        e->yaw += xrel * e->theta; 
        e->xaw += yrel * e->theta;
    }
}

void                camera_rot_mouse(t_env *e)
{
    if (e->key[MOUSE])
    {
	    SDL_GetGlobalMouseState(&(e->mouse.x), &(e->mouse.y));
	    SDL_GetRelativeMouseState(&(e->mouse.xrel), &(e->mouse.yrel));
        camera_rot_mouse_calc(e);
        
        if (abs(e->mouse.xrel) > W_W / 2 || abs(e->mouse.yrel) > W_H / 2
	    || e->mouse.x > e->wx + W_W - 1
	    || e->mouse.x < e->wx
	    || e->mouse.y > e->wy + W_H - 1
	    || e->mouse.y < e->wy)
	    	SDL_WarpMouseGlobal(e->wx + (W_W / 2),
	    		e->wy + (W_H / 2));
    	SDL_FlushEvent(SDL_MOUSEMOTION);
        e->key[MOUSE] = 0;
    }
}


void                camera_rot_event(t_env *e)
{
    camera_rot_mouse(e);
    if (e->key[LEFT])
        e->yaw -= 8.0 * e->theta;
    if (e->key[RIGHT])
        e->yaw += 8.0 * e->theta;
    if (e->key[UP])
        e->xaw -= 8.0 * e->theta;
    if (e->key[DOWN])
        e->xaw += 8.0 * e->theta;
}

static void         camera_move_event(t_env *e)
{
    t_vec   forward;
    t_vec   right;

    forward = vectormult(e->vlist.lookdir, 8.0 * e->theta * e->usr.shift);
    right = vectormult((t_vec){forward.z, 0, -forward.x, forward.w}, 0.5f);
    if (e->key[W])
        e->vlist.vcamera = vectoradd(e->vlist.vcamera, forward);
    if (e->key[S])
        e->vlist.vcamera = vectorsub(e->vlist.vcamera, forward);
    if (e->key[A])
        e->vlist.vcamera = vectoradd(e->vlist.vcamera, right);
    if (e->key[D])
        e->vlist.vcamera = vectorsub(e->vlist.vcamera, right); 
    if (e->key[SPACE])
        e->vlist.vcamera.y += 8.0 * e->theta;
    if (e->key[LCTRL])
        e->vlist.vcamera.y -= 8.0 * e->theta;
}

void                camera_event(t_env *e)
{
    camera_move_event(e);
    camera_rot_event(e);
    if (e->key[SHIFT])
        e->usr.shift = 4;
    else
        e->usr.shift = 2;
}