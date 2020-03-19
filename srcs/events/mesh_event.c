/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 16:14:18 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void                mesh_rot_event(t_env *e)
{
    if (e->key[NUM8])
        e->mesh[e->mesh_id].xtheta += 2.0 * e->theta;
    if (e->key[NUM5])
        e->mesh[e->mesh_id].xtheta -= 2.0 * e->theta;
    if (e->key[NUM7])
        e->mesh[e->mesh_id].ytheta -= 2.0 * e->theta;
    if (e->key[NUM9])
        e->mesh[e->mesh_id].ytheta += 2.0 * e->theta;
    if (e->key[NUM4])
        e->mesh[e->mesh_id].ztheta -= 2.0 * e->theta;
    if (e->key[NUM6])
        e->mesh[e->mesh_id].ztheta += 2.0 * e->theta;
}