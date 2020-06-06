/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 23:28:46 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 17:15:20 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            init_world(t_env *e)
{
    int i;

    e->obj_on_world = e->nbmesh;
    printf("OBJ: %d\n", e->obj_on_world);
    i = -1;
    while (++i < e->obj_on_world)
        e->world_obj = ft_list_push_back(e->world_obj, &e->mesh[i], sizeof(t_mesh));
    ft_listindex(e->world_obj);
    print_objlist(e->world_obj);
}