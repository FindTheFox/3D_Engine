/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 16:14:18 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/05 23:39:52 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void                switch_i_mesh(t_env *e, t_mesh *obj)
{
    if (e->key[NUM0])
    {
        if (e->usr.select_mesh < e->obj_on_world - 1)
            ++e->usr.select_mesh;
        else
            e->usr.select_mesh = 0;
        if (!(obj = (t_mesh*)ft_listfind(&e->world_obj, e->usr.select_mesh)))
            ft_exit(e, "DooM: echec obj access\n", 0);
        ft_putstr("Selected MESH:   ");
        ft_putendl(obj->name);
        e->key[NUM0] = 0;
    }
}

static void                switch_mesh_mod(t_env *e)
{
    if (e->key[PAD_ENTER])
    {
        e->usr.opt_mesh = e->usr.opt_mesh == 0 ? 1 : 0;
        e->usr.opt_mesh == 1 ? ft_putstr("OPT: MOVE MESH\n") : 0;
        e->usr.opt_mesh == 0 ? ft_putstr("OPT: ROT MESH\n") : 0;
        e->key[PAD_ENTER] = 0;
    }
}

static void         move_event(t_env *e, t_mesh *obj)
{
    t_vec   forward;
    t_vec   right;

    forward = vectormult(e->vlist.lookdir, 8.0 * e->theta);
    vectormult(forward, 0.5);
    right = vectormult((t_vec){forward.z, 0, -forward.x, forward.w}, 0.5f);
    vectormult(right, 0.5);
    //printf("2X : %f      Y: %f       Z: %f\n", right.x, right.y, right.z);
    
    if (e->key[NUM8])
        obj->dir = vectoradd(obj->dir, forward);
    if (e->key[NUM5])
        obj->dir = vectorsub(obj->dir, forward);
    if (e->key[NUM4])
        obj->dir = vectoradd(obj->dir, right);
    if (e->key[NUM6])
        obj->dir = vectorsub(obj->dir, right); 
    if (e->key[PLUS])
        obj->dir.y += 8.0 * e->theta;
    if (e->key[MINUS])
        obj->dir.y -= 8.0 * e->theta;
    if (e->key[NUM7])
        obj->ytheta -= 2.0 * e->theta;
    if (e->key[NUM9])
        obj->ytheta += 2.0 * e->theta;
}

static void          rot_event(t_env *e, t_mesh *obj)
{
    if (e->key[NUM8])
        obj->xtheta += 2.0 * e->theta;
    if (e->key[NUM5])
        obj->xtheta -= 2.0 * e->theta;
    if (e->key[NUM7])
        obj->ytheta -= 2.0 * e->theta;
    if (e->key[NUM9])
        obj->ytheta += 2.0 * e->theta;
    if (e->key[NUM4])
        obj->ztheta -= 2.0 * e->theta;
    if (e->key[NUM6])
        obj->ztheta += 2.0 * e->theta;
}

void                mesh_rot_event(t_env *e, int index_mesh)
{
    t_mesh *obj;

    obj = NULL;
    if (e->usr.forge)
    {
        if (!(obj = ft_listfind(&e->world_obj, index_mesh)))
            ft_exit(e, "DooM: Pull obj in dyntab failed\n", 0);
        switch_i_mesh(e, obj);
        switch_mesh_mod(e);
        if (e->usr.forge)
        {
            e->usr.opt_mesh == 0 ? move_event(e, obj) : 0; 
            e->usr.opt_mesh == 1 ? rot_event(e, obj) : 0;
        }
    }
}