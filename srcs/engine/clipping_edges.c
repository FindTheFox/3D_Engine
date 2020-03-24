/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping_edges.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 22:21:24 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/22 23:37:27 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void         small_triangle(t_clip clip, t_triangle out[2], t_vec vec[2])
{
    float t;

    out[0].p[0] = clip.in[0];
    out[0].tx[0] = clip.tx_in[0];

    out[0].p[1] = vec_inter_plane(vec, clip.in[0], clip.out[0], &t);
    out[0].tx[1].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[1].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v;
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;
    
    out[0].p[2] = vec_inter_plane(vec, clip.in[0], clip.out[1], &t);
    out[0].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v;
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;
}

void          quad_triangle(t_clip clip, t_triangle out[2], t_vec vec[2])
{
    float t;

    out[0].p[0] = clip.in[0];
    out[0].p[1] = clip.in[1];
    out[0].tx[0] = clip.tx_in[0];
    out[0].tx[1] = clip.tx_in[1];
    
    out[0].p[2] = vec_inter_plane(vec, clip.in[0], clip.out[0], &t);
    out[0].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v; 
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;

    out[1].p[0] = clip.in[1];
    out[1].p[1] = out[0].p[2];
    out[1].tx[0] = clip.tx_in[1];
    out[1].tx[1] = out[0].tx[2];

    out[1].p[2] = vec_inter_plane(vec, clip.in[1], clip.out[0], &t);
    out[1].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[1].u) + clip.tx_in[1].u;
    out[1].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[1].v) + clip.tx_in[1].v; 
    out[1].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[1].w) + clip.tx_in[1].w;
}

void        sort_triangle(t_clip *clip, t_triangle in)
{
    int i;

    i = 0;
    clip->inside = 0;
    clip->outside = 0;
    clip->tx_inside = 0;
    clip->tx_outside = 0;
    while (i < 3)
    {
        if (clip->d[i] >= 0)
        {
            clip->in[clip->inside++] = in.p[i];
            clip->tx_in[clip->tx_inside++] = in.tx[i];
        }
        else
        {
            clip->out[clip->outside++] = in.p[i];
            clip->tx_out[clip->tx_outside++] = in.tx[i];
        }
        i++;
    }
}

static void             init_to_raster(t_env *e, t_dyntab *to_raster, t_triangle t)
{
    t_triangle  tmp;
    int         point;
    int         i;

    if (triangle_in_edges(t))
    {
        push_dynarray(to_raster, &t, false);
        return ;
    }
    point = 0;
    clip_edges(&e->clip_tab[0], t, point++);
    while (point < 4)
    {
        i = -1;
        while (++i < e->clip_tab[point - 1].cell_nb)
            clip_edges(to_raster, *(t_triangle *)dyaddress(&e->clip_tab[point - 1], i), point);            
        clear_dynarray(&e->clip_tab[point - 1]);
        point++;
    }
    i = -1;
    while (++i < e->clip_tab[3].cell_nb)
        push_dynarray(to_raster, dyaddress(&e->clip_tab[3], i), 0);
    clear_dynarray(&e->clip_tab[3]);
}

void            clip_mesh(t_env *e, t_dyntab *to_clip, t_dyntab *to_raster)
{
    t_triangle  *t;
    int         i;

    i = 0;
    while (i < to_clip->cell_nb)
    {
        t = dyaddress(to_clip, i);
        init_to_raster(e, to_raster, *t);
        i++;
    }
}
