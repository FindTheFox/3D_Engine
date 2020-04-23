/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:23:48 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:57:47 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

int         allocate_clip_tab(t_dyntab arr[4])
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (init_dynarray(&arr[i], sizeof(t_triangle), MIN_TO_CLIP))
            return (-1);
        i++;
    }
    return (0);
}

void       init_dynamic_tab(t_env *e)
{
    if (allocate_clip_tab(e->clip_tab)
        || init_dynarray(&e->to_clip, sizeof(t_triangle), MIN_TO_RASTER)
        || init_dynarray(&e->to_raster, sizeof(t_triangle), MIN_TO_RASTER))
        ft_exit(e, "dynamic array init fail", 0);
}