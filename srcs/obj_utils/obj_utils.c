/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 15:41:37 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/25 16:37:05 by qbenaroc         ###   ########.fr       */
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
    }
}

void            pop_obj(t_env *e, t_mesh *push, t_vec pos)
{
    push->id = e->obj_on_world;
    e->obj_on_world += 1;
    print_objlist(e->world_obj);
    printf("POP: %s\n", push->name);
    e->world_obj = ft_list_push_back(e->world_obj, push, sizeof(t_mesh));
    ft_listindex(e->world_obj);
	place_obj(push, pos);
}

void            remove_obj(t_env *e, int id)
{
    int     i;
    t_list  *tmp;
    t_mesh  *obj;

    if (!(e->world_obj = ft_lstremove(e->world_obj, id)))
        e->obj_on_world = -1;
    else
        e->obj_on_world--;
    e->usr.select_mesh = 0;
    ft_listindex(e->world_obj);
}

void            select_save_obj(t_env *e, int id)
{
    if (id >= e->nbmesh)
        id = 0;
    e->usr.new_obj = id;
    ft_putstr("New Mesh:    ");
    ft_putendl(e->mesh[id].name);
}
