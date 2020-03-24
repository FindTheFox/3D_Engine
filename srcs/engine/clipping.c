/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:46:17 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/23 05:42:48 by saneveu          ###   ########.fr       */
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

int                 make_triangle_clipped(t_clip *clip, t_triangle out[2], t_vec vec[2], t_triangle in)
{
    float   t;
    
    if (clip->inside == 1 && clip->outside == 2)
    {
        out[0].color = in.color;//0x0000ff;
        small_triangle(*clip, out, vec);       
        return (1);
    }
    else if (clip->inside == 2 && clip->outside == 1)
    {
        out[0].color = in.color;//0xff0000;
        out[1].color = in.color;//0x00ff00;
        quad_triangle(*clip, out, vec);
        return (2);
    }
    return (0);
}

int         clip_triangle_by_plane(t_vec plane_p, t_vec plane_n, t_triangle in, t_triangle out[2])
{
    t_clip  clip;
    int     ret;
    
    plane_n = vectornormal(plane_n);
    //printf("----start----\nx %f || y %f || z %f\n\n", plane_n.x, plane_n.y, plane_n.z);

    clip.d[0] = vectorproduct(plane_n, in.p[0]) - vectorproduct(plane_n, plane_p);
    clip.d[1] = distance_to_plane(plane_p, plane_n, in.p[1]);
    clip.d[2] = distance_to_plane(plane_p, plane_n, in.p[2]);

    sort_triangle(&clip, in);
    if (clip.inside == 0)
        return (0);
    else if (clip.inside == 3)
    {
        out[0] = in;
        return (1);
    }
    else
    {
        ret = make_triangle_clipped(&clip, out, (t_vec[2]){plane_p, plane_n}, in);
        return(ret);
    }
}

void                    clip_edges(t_dyntab *to_raster, t_triangle t, int point)
{
    t_triangle      clip[2];
    int             tris_to_add;
    int             i;

    tris_to_add = 0;
    if (point == 0)
        tris_to_add = clip_triangle_by_plane((t_vec){(float)W_W,0,0,1}, (t_vec){-1.0f,0 , 0, 1}, t, clip);
    else if (point == 1)
        tris_to_add = clip_triangle_by_plane((t_vec){0,0,0,1}, (t_vec){1,0,0,1}, t, clip);
    else if (point == 2)
        tris_to_add = clip_triangle_by_plane((t_vec){0,0,0,1}, (t_vec){0,1,0,1}, t, clip);
    else if (point == 3)
        tris_to_add = clip_triangle_by_plane((t_vec){0,(float)W_H,0,1}, (t_vec){0,1.0f,0,1}, t, clip);
    i = -1;
    while (++i < tris_to_add)
        if (push_dynarray(to_raster, &clip[i], 0))
            return ;
}

void            rasterizer(t_env *e, t_dyntab *to_clip)
{
    t_triangle  *t;
    t_thread    thread[NB_THREAD];
    int         i;

    clip_mesh(e, to_clip, &e->to_raster);
    i = 0; 
    /*while (i < NB_THREAD)
    {
        thread[i].id = i;
        thread_init(e, &thread[i]);
        ++i;
    }

    i = 0;
    while (i < NB_THREAD)
    {
        pthread_join(thread[i].thread, NULL);
        i++;
    }*/
    
    while (i < e->to_raster.cell_nb)
    {
        t = (t_triangle *)dyaddress(&e->to_raster, i);
        //printf("color %x\n", t->color);
        fill_triangle(e, t, t->color);
        draw_triangle(e, *t);
        //fill_triangle_texture(e, *t);
        i++;
    }
    clear_dynarray(&e->to_raster);
}