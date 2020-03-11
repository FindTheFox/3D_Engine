/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/11 16:52:56 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

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
    thread->end = thread->start + todo;
    if (pthread_create(&thread->thread, NULL, do_thread, (void *)thread))
        ft_exit(e, "thread create failed", 0);
}