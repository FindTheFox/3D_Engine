/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:41:37 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/04 18:05:31 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            place_obj(t_mesh *obj, t_vec pos)
{
    obj->dir = pos;
}

void            drag_and_drop(t_env *e, t_mesh *obj, float x, float y)
{
    t_vec   forward;
    t_vec   right;
    t_vec   up;

    forward = vectormult(e->vlist.lookdir, 8.0 * e->theta);
    forward.y = 0;
    up = (t_vec){0, 0.1, 0, 1};
    right = vectormult((t_vec){forward.z, 0, -forward.x, forward.w}, 0.5f);
    vectordiv(right, 2);
    if (x < 0)
    {
        right = vectormult(right, -x / 2.5);
        obj->dir = vectoradd(obj->dir, right);
    }
    if (x > 0)
    {
        right = vectormult(right, x / 2.5);
        obj->dir = vectorsub(obj->dir, right);
    }
    if (y != 0)
    {
        forward = vectormult(forward, y / 2);
        obj->dir = vectorsub(obj->dir, forward);
        //up = vectormult(up, x / 4);
        //obj->dir = vectorsub(obj->dir, up);
        //obj->dir = vectorsub(obj->dir, right);
    }
}