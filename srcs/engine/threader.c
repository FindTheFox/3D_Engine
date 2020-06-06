/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/06/06 14:33:50 by brpinto          ###   ########.fr       */
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
    while (++thread->i < thread->end)
    {
        t = (t_triangle*)dyaddress(&thread->tris, thread->i);
        //fill_triangle(e, t, t->color);
        if (e->usr.fill_text)
            fill_triangle_texture(e, *t);
        if (e->usr.draw_line)
            draw_triangle(e, *t);
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
    thread->mode = e->usr.mode;
    thread->tris = e->to_raster;
    thread->start = thread->id * todo;
    thread->i = thread->start - 1;
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
        //printf("RASTER THREAD JOIN\n");
        pthread_join(thread[i].thread, NULL);
        i++;
    }
    
    //while (i < e->to_raster.cell_nb)
    //{
    //    t = (t_triangle *)dyaddress(&e->to_raster, i);
    //    //printf("color %x\n", t->color);
    //    //fill_triangle(e, t, t->color);
    //    fill_triangle_texture(e, *t);
    //    //draw_triangle(e, *t);
    //    i++;
    //}
    
}

static  void    obj_thread_init(t_env *e, t_thread *t, void *f(void *))
{
    if (!(t->obj = (t_mesh*)ft_listfind(&e->world_obj, t->id)))
            ft_exit(e, "DooM: list find echec\n", 0);
    if (allocate_clip_tab(t->clip_tab)
        || init_dyntab(&t->to_clip, sizeof(t_triangle), MIN_TO_RASTER)
        || init_dyntab(&t->to_raster, sizeof(t_triangle), MIN_TO_RASTER))
        ft_exit(e, "dynamic array init fail", 0);
    t->env = e;
    t->start = t->id;
    t->end = t->start + 1;
    t->mlist = e->mlist;
    t->vlist = e->vlist;
    if (pthread_create(&t->thread, NULL, f, (void *)t))
        ft_exit(e, "thread create platforming failed\n", 0);
}

void        obj_thread(t_env *e, t_thread *threads, void *f(void *))
{
    int i;
    //t_thread    threads[e->obj_on_world];

    i = -1;
    while (++i < e->obj_on_world)
    {
        //printf("THREAD OBJ : %d\n", i);
        threads[i].id = i;
        obj_thread_init(e, &threads[i], f);
    }
    i = -1;
    while (++i < e->obj_on_world)
        pthread_join(threads[i].thread, NULL);
}
