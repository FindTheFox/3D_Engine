/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/03 19:04:18 by saneveu          ###   ########.fr       */
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
        //fill_triangle(e, t, t->color);
        fill_triangle_texture(e, *t);
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