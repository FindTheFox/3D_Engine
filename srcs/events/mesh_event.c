/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 16:14:18 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/02 02:58:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void                switch_i_mesh(t_env *e)
{
    if (e->key[NUM0])
    {
        if (e->usr.select_mesh < e->nbmesh - 1)
            ++e->usr.select_mesh;
        else
            e->usr.select_mesh = 0;
        printf("Selected MESH: %s\n", e->mesh[e->usr.select_mesh].name);
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

static void         move_event(t_env *e, int i)
{
    t_vec   forward;
    t_vec   right;

    forward = vectormult(e->vlist.lookdir, 8.0 * e->theta);
    vectormult(forward, 0.5);
    right = vectormult((t_vec){forward.z, 0, -forward.x, forward.w}, 0.5f);
    vectormult(right, 0.5);
    if (e->key[NUM8])
        e->mesh[i].dir = vectoradd(e->mesh[i].dir, forward);
    if (e->key[NUM5])
        e->mesh[i].dir = vectorsub(e->mesh[i].dir, forward);
    if (e->key[NUM4])
        e->mesh[i].dir = vectoradd(e->mesh[i].dir, right);
    if (e->key[NUM6])
        e->mesh[i].dir = vectorsub(e->mesh[i].dir, right); 
    if (e->key[PLUS])
        e->mesh[i].dir.y += 8.0 * e->theta;
    if (e->key[MINUS])
        e->mesh[i].dir.y -= 8.0 * e->theta;
    if (e->key[NUM7])
        e->mesh[i].ytheta -= 2.0 * e->theta;
    if (e->key[NUM9])
        e->mesh[i].ytheta += 2.0 * e->theta;
}

static void          rot_event(t_env *e, int i)
{
    if (e->key[NUM8])
        e->mesh[i].xtheta += 2.0 * e->theta;
    if (e->key[NUM5])
        e->mesh[i].xtheta -= 2.0 * e->theta;
    if (e->key[NUM7])
        e->mesh[i].ytheta -= 2.0 * e->theta;
    if (e->key[NUM9])
        e->mesh[i].ytheta += 2.0 * e->theta;
    if (e->key[NUM4])
        e->mesh[i].ztheta -= 2.0 * e->theta;
    if (e->key[NUM6])
        e->mesh[i].ztheta += 2.0 * e->theta;
}

void                mesh_rot_event(t_env *e, int index_mesh)
{
    if (e->usr.forge)
    {
        switch_i_mesh(e);
        switch_mesh_mod(e);
        e->usr.opt_mesh == 0 ? move_event(e, e->usr.select_mesh) : 0; 
        e->usr.opt_mesh == 1 ? rot_event(e, e->usr.select_mesh) : 0;
    }
}