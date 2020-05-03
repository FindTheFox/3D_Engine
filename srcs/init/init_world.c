/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:28:46 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/04 00:13:22 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            init_world(t_env *e)
{
    int i;

    e->obj_on_world = e->nbmesh;
    printf("OBJ: %d\n", e->obj_on_world);
    if (init_dynarray(&e->world_obj, sizeof(t_mesh), e->obj_on_world))
        ft_exit(e, "DooM: Fail tabdyn", 0);
    i = -1;
    while (++i < e->obj_on_world)
        push_dynarray(&e->world_obj, &e->mesh[i], 0);
}