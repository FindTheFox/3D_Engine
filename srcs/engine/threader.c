/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/10 19:46:14 by saneveu          ###   ########.fr       */
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
        fill_triangle(e, t, t->color);
        //fill_triangle_texture(e, *t);
        draw_triangle(e, *t);
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