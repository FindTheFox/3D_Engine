/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/28 00:57:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            *do_thread(void *param)
{
    t_thread    *thread;
    t_triangle  *t;
    t_env       *e;

    thread = (t_thread *)param;
    e = (t_env*)thread->env;
    while (thread->i < thread->end)
    {
        t = (t_triangle*)dyaddress(&thread->tris, thread->i);
        //printf("w1: %f, w2: %f, w3: %f\n", t->tx[0].w, t->tx[1].w, t->tx[2].w);
        //fill_triangle(e, t, t->color);
        fill_triangle_texture(e, *t);
        //draw_triangle(e, *t);
        thread->i++;
    }
    pthread_exit(NULL);
}

void            thread_init(t_env *e, t_thread *thread)
{
    int todo;
    int rest;
    todo = (e->to_raster.cell_nb / NB_THREAD);
    rest = (e->to_raster.cell_nb % NB_THREAD);
    thread->env = e;
    thread->tris = e->to_raster;
    thread->start = thread->id * todo;
    thread->i = thread->start;
    thread->end = thread->start + todo + (thread->id == NB_THREAD - 1 ? rest : 0);
    if (pthread_create(&thread->thread, NULL, do_thread, (void *)thread))
        ft_exit(e, "thread create failed", 0);
}

void            rasterizer(t_env *e, t_dyntab *to_clip)
{
    t_triangle  *t;
    t_thread    thread[NB_THREAD];
    int         i;

    clip_mesh(e, to_clip, &e->to_raster);
    // thread_init(e);
    i = 0;
    while (i < NB_THREAD)
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
    }
    /*
    while (i < e->to_raster.cell_nb)
    {
        t = (t_triangle *)dyaddress(&e->to_raster, i);
        //printf("color %x\n", t->color);
        fill_triangle(e, t, t->color);
        //fill_triangle_texture(e, *t);
        //draw_triangle(e, *t);
        i++;
    }
    */
    clear_dynarray(&e->to_raster);
}