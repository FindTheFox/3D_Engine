/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dengine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:18:31 by saneveu           #+#    #+#             */
/*   Updated: 2020/06/06 14:40:15 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        texture_perspective(t_triangle *t)
{
    t->tx[0].u /= t->p[0].w;
    t->tx[1].u /= t->p[1].w;
    t->tx[2].u /= t->p[2].w;

    t->tx[0].v /= t->p[0].w;
    t->tx[1].v /= t->p[1].w;
    t->tx[2].v /= t->p[2].w;

    t->tx[0].w = 1.0f / t->p[0].w;
    t->tx[1].w = 1.0f / t->p[1].w;
    t->tx[2].w = 1.0f / t->p[2].w;
}

void        projection2(t_thread *t, t_triangle triclip, int color)
{
    t_triangle triproj;

    matrix_mult_triangle(t->mlist.matproj, &triclip);

    triproj = triclip;
    texture_perspective(&triproj);
    
    triproj.p[0] = vectordiv(triproj.p[0], triproj.p[0].w);
    triproj.p[1] = vectordiv(triproj.p[1], triproj.p[1].w);
    triproj.p[2] = vectordiv(triproj.p[2], triproj.p[2].w); 

    //Scale
    triproj.p[0] = vectoradd(triproj.p[0], t->vlist.voff_set);
    triproj.p[1] = vectoradd(triproj.p[1], t->vlist.voff_set);
    triproj.p[2] = vectoradd(triproj.p[2], t->vlist.voff_set);

    //X/Y are inverted ?
    //triproj.p[0] = vectormult(triproj.p[0], -1.0f);
    //triproj.p[1] = vectormult(triproj.p[1], -1.0f);
    //triproj.p[2] = vectormult(triproj.p[2], -1.0f);

    center(&triproj.p[0]);
    center(&triproj.p[1]);
    center(&triproj.p[2]);
    
    triproj.color = color;
    if (push_dyntab(&t->to_clip, &triproj, false))
        ft_exit((t_env*)&t->env, "push dynamic tab to_clip fail", 0);
}

void        projection(t_thread *t, t_triangle triprojected, int color)
{
    t_triangle  clip[2];
    t_triangle  tview;
    int         i;
    int         nclip;

    matrix_mult_triangle(t->mlist.matview, &triprojected);
    nclip = clip_triangle_by_plane((t_vec){0,0,0.5f,1.0f}, (t_vec){0,0,0.1,1.0f}, &triprojected, clip);

    i = -1;
    while (++i < nclip)
        projection2(t, clip[i], color);
}

static int        normalize(t_thread *t, t_triangle tri, int *color)
{
    t_vec   normal;
    t_vec   line1;
    t_vec   line2;
    t_vec   vcamray;

    line1 = vectorsub(tri.p[1], tri.p[0]);
    line2 = vectorsub(tri.p[2], tri.p[0]);
    normal = vectorcrossprod(line1, line2);
    normal = vectornormal(normal);
    vcamray = vectorsub(tri.p[0], t->vlist.vcamera);
    if (vectorproduct(normal, vcamray) < 0)
    {
        lumiere(t, normal, color);
        return (1);
    }
    return (0);
}

void        *project_tri(void *thread)
{
    t_env       *e;
    t_thread    *t;
    t_triangle  triproj;
    int         j;
    int         color;

    t = (t_thread*)thread;
    e = (t_env*)t->env;
    matrix_world(t, t->obj);
    j = -1;
    while (++j < t->obj->size)
    {
        triproj = t->obj->tris[j];
        pass_data(&triproj, t->obj->tris[j]);
        triproj.mesh_id = t->obj->id;
        matrix_mult_triangle(t->mlist.matworld, &triproj);
        color = t->obj->color;
        if (normalize(t, triproj, &color) == 1)
            projection(t, triproj, color);
    }
    clip_mesh(e, &t->to_clip, &t->to_raster);
    rasterizer(e, &t->to_raster);
}

void        engine_3d(t_env *env)
{
    int         i;
    t_mesh      *obj;
    t_thread    threads[env->obj_on_world];
    t_thread    t;

    //do_camera rot/move
    matrix_view(env);
    if (env->obj_on_world == -1)
        return ;
    //env->mesh_id = -1;
    //if (!(obj = (t_mesh*)ft_listfind(&env->world_obj, i)))
    //    ft_exit(env, "DooM: list find echec\n", 0);
    i = -1;
    obj_thread(env, threads, project_tri);
    //swhile (++i < env->obj_on_world)
    //s{
    //s    printf("rasterize obj : %d\n", i);
    //s    rasterizer(env, &threads[i].to_clip);
    //s    free_dyntab(&threads[i].to_clip);
    //s    free_dyntab(&threads[i].to_raster);
    //s}
}
