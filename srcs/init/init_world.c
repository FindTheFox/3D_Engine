/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:28:46 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/06 01:18:50 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            init_world(t_env *e)
{
    int i;

    e->obj_on_world = e->nbmesh;
    printf("OBJ: %d\n", e->obj_on_world);
    //if (init_dyntab(&e->world_obj, sizeof(t_mesh), e->obj_on_world))
    //    ft_exit(e, "DooM: Fail tabdyn", 0);
    i = -1;
    //while (++i < e->obj_on_world)
    //    push_dyntab(&e->world_obj, &e->mesh[i], 0);
    while (++i < e->obj_on_world)
        ft_list_push_back(&e->world_obj, &e->mesh[i], sizeof(t_mesh));
}