/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_edges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:41:15 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 21:27:57 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

int                     triangle_in_edges(t_triangle t)
{
    int i;

    i = -1;
    while (++i < 3)
        if (t.p[i].x < 0 || t.p[i].x >= W_W
            || t.p[i].y < 0 || t.p[i].y >= W_H)
            return (0);
    return (1);
}

void                    clip_edges(t_dyntab *to_raster, t_triangle t, int point)
{
    t_triangle      clip[2];
    int             tris_to_add;
    int             i;

    //printf("t->meshid: %d\n", t.mesh_id);
    tris_to_add = 0;
    if (point == 0)
        tris_to_add = clip_triangle_by_plane((t_vec){0,(float)W_H,0,1}, (t_vec){0,-1.0f,0,1}, &t, clip);
    else if (point == 1)
        tris_to_add = clip_triangle_by_plane((t_vec){0,0,0,1}, (t_vec){0,1,0,1}, &t, clip);
    else if (point == 2)
        tris_to_add = clip_triangle_by_plane((t_vec){(float)W_W,0,0,1}, (t_vec){-1.0f,0 , 0, 1}, &t, clip);
    else if (point == 3)
        tris_to_add = clip_triangle_by_plane((t_vec){0,0,0,1}, (t_vec){1,0,0,1}, &t, clip);
    i = -1;
    while (++i < tris_to_add)
    {
        pass_data(&clip[i], t);
        if (push_dyntab(to_raster, &clip[i], 0))
            return ;
    }
}

static void             init_to_raster(t_env *e, t_dyntab *to_raster, t_triangle t)
{
    t_triangle  *tmp;
    int         point;
    int         i;

    if (triangle_in_edges(t))
    {
        push_dyntab(to_raster, &t, false);
        return ;
    }
    point = -1;
    clip_edges(&e->clip_tab[0], t, ++point);
    while (++point < 4)
    {
        i = -1;
        while (++i < e->clip_tab[point - 1].cell_nb)
            clip_edges(&e->clip_tab[point], *(t_triangle *)dyaddress(&e->clip_tab[point - 1], i), point);
        clear_dyntab(&e->clip_tab[point - 1]);

    }
    tmp = (t_triangle*)dyaddress(&e->clip_tab[3], 0);
    i = -1;
    while (++i < e->clip_tab[3].cell_nb)
        push_dyntab(to_raster, dyaddress(&e->clip_tab[3], i), 0);
    clear_dyntab(&e->clip_tab[3]);
}    

void            clip_mesh(t_env *e, t_dyntab *to_clip, t_dyntab *to_raster)
{
    t_triangle  *t;
    int         i;

    i = 0;
    while (i < to_clip->cell_nb)
    {
        t = (t_triangle*)dyaddress(to_clip, i);
        init_to_raster(e, to_raster, *t);
        i++;
    }
}