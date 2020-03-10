/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:46:17 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/09 20:08:44 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"


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

int         make_triangle_clipped(t_clip *clip, t_triangle out[2], t_vec vec[2], t_triangle in)
{
    if (clip->inside == 1 && clip->outside == 2)
    {
        out[0].color = in.color;
        out[0].p[0] = clip->in[0];
        out[0].p[1] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[0]);
        out[0].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[1]);
        return (1);
    }
    else if (clip->inside == 2 && clip->outside == 1)
    {
        out[0].color = in.color;
        out[1].color = in.color;
        out[0].p[0] = clip->in[0];
        out[0].p[1] = clip->in[1];
        out[0].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[0]);

        out[1].p[0] = clip->in[1];
        out[1].p[1] = out[0].p[2];
        out[1].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[1], clip->out[0]);
        return (2);
    }
    return (0);
}

void        sort_triangle(t_clip *clip, t_triangle in)
{
    int i;

    i = 0;
    clip->inside = 0;
    clip->outside = 0;
    while (i < 3)
    {
        if (clip->d[i] >= 0)
            clip->in[clip->inside++] = in.p[i];
        else
            clip->out[clip->outside++] = in.p[i];
        i++;
    }
}

int         clip_triangle(t_vec plane_n, t_vec plane_p, t_triangle in, t_triangle out[2])
{
    t_clip  clip;
    
    // plane_n = vectornormal(plane_n);
    //plane = (t_vec[2]){plane_p, plane_n};

    clip.d[0] = distance_to_plane(plane_n, plane_p, in.p[0]);
    clip.d[1] = distance_to_plane(plane_n, plane_p, in.p[1]);
    clip.d[2] = distance_to_plane(plane_n, plane_p, in.p[2]);

    sort_triangle(&clip, in);
    if (clip.inside == 0)
        return (0);
    else if (clip.inside == 3)
    {
        out[0] = in;
        return (1);
    }
    else
        return(make_triangle_clipped(&clip, out, (t_vec[2]){plane_n, plane_p}, in));
}

void                    clip_edges(t_dyntab *to_raster, t_triangle t, int point)
{
    t_triangle      clip[2];
    int             to_add;
    int             i;

    to_add = 0;
    if (point == 0)
        to_add = clip_triangle((t_vec){0,0,0,0}, (t_vec){0,1.0f,0,0}, t, clip);
    else if (point == 1)
        to_add = clip_triangle((t_vec){0,(float)W_H - 1,0,0}, (t_vec){0,-1.0f,0,0}, t, clip);
    else if (point == 2)
        to_add = clip_triangle((t_vec){0,0,0,0}, (t_vec){1.0f,0,0,0}, t, clip);
    else if (point == 3)
        to_add = clip_triangle((t_vec){(float)W_W - 1,0,0,0}, (t_vec){-1.0f,0,0,0}, t, clip);
    i = 0;
    while (i < to_add)
    {
        clip[i].color = t.color;
        if (push_dynarray(to_raster, &clip[i], 0))
            return ;
        ++i;
    }
}

static void             init_to_raster(t_dyntab *to_raster, t_dyntab clip_tab[4], t_triangle t)
{
    t_triangle  tmp;
    int         point;
    int         i;

    if (triangle_in_edges(t))
    {
        push_dynarray(to_raster, &t, false);
        return ;
    }
    clip_edges(&clip_tab[0], t, 0);
    point = 1;
    while (point < 4)
    {
        i = 0;
        while (i < clip_tab[point - 1].cell_nb)
        {
            tmp = *(t_triangle *)dyacc(&clip_tab[point - 1], i);
            clip_edges(&clip_tab[point], tmp, point);            
            i++;
        }
        clear_dynarray(&clip_tab[point - 1]);
        point++;
    }
    i = -1;
    while (++i < clip_tab[3].cell_nb)
        push_dynarray(to_raster, dyacc(&clip_tab[3], i), 0);
    clear_dynarray(&clip_tab[3]);
}    

static void            clip_mesh(t_dyntab *to_clip, t_dyntab *to_raster, t_dyntab clip_tab[4])
{
    t_triangle  *t;
    int         i;

    i = 0;
    while (i < to_clip->cell_nb)
    {
        t = dyacc(to_clip, i);
        init_to_raster(to_raster, clip_tab, *t);
        i++;
    }
    i = -1;
    while (++i < 4)
        clear_dynarray(&clip_tab[i]);
}

void            rasterizer(t_env *e, t_dyntab *to_clip)
{
    t_triangle  t;
    // t_thread    thread[NB_THREAD];
    int         i;

    clip_mesh(to_clip, &e->to_raster, e->clip_tab);
    // thread_init(e);
    i = 0;
    // while (i < NB_THREAD)
    // {
    //     thread[i].id = i;
    //     thread_init(e, &thread[i]);
    //     ++i;
    // }
    // i = 0;
    // while (i < NB_THREAD)
    // {
    //     pthread_join(thread[i].thread, NULL);
    //     i++;
    // }
    
    while (i < e->to_raster.cell_nb)
    {
        t = *(t_triangle *)dyacc(&e->to_raster, i);
        fill_triangle(e, t, t.color);
        i++;
    }
    clear_dynarray(&e->to_raster);
}