/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dengine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:18:31 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/08 00:38:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        texture_perspective(t_env *env, t_triangle *t)
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

void        projection2(t_env *env, t_triangle triclip, int color)
{
    t_triangle triproj;

    matrix_mult_triangle(env->mlist.matproj, &triclip);

    triproj = triclip;
    texture_perspective(env, &triproj);
    
    triproj.p[0] = vectordiv(triproj.p[0], triproj.p[0].w);
    triproj.p[1] = vectordiv(triproj.p[1], triproj.p[1].w);
    triproj.p[2] = vectordiv(triproj.p[2], triproj.p[2].w); 

    //Scale
    triproj.p[0] = vectoradd(triproj.p[0], env->vlist.voff_set);
    triproj.p[1] = vectoradd(triproj.p[1], env->vlist.voff_set);
    triproj.p[2] = vectoradd(triproj.p[2], env->vlist.voff_set);

    //X/Y are inverted ?
    //triproj.p[0] = vectormult(triproj.p[0], -1.0f);
    //triproj.p[1] = vectormult(triproj.p[1], -1.0f);
    //triproj.p[2] = vectormult(triproj.p[2], -1.0f);

    center(&triproj.p[0]);
    center(&triproj.p[1]);
    center(&triproj.p[2]);
    
    triproj.color = color;
    if (push_dyntab(&env->to_clip, &triproj, false))
        ft_exit(env, "push dynamic tab to_clip fail", 0);
}

void        projection(t_env *env, t_triangle triprojected, int color)
{
    t_triangle  clip[2];
    t_triangle  tview;
    int         i;
    int         nclip;

    matrix_mult_triangle(env->mlist.matview, &triprojected);
    nclip = clip_triangle_by_plane((t_vec){0,0,0.5f,1.0f}, (t_vec){0,0,0.1,1.0f}, &triprojected, clip);

    i = -1;
    while (++i < nclip)
        projection2(env, clip[i], color);
}

static int        normalize(t_env *e, t_triangle tri, int *color)
{
    t_vec   normal;
    t_vec   line1;
    t_vec   line2;
    t_vec   vcamray;

    line1 = vectorsub(tri.p[1], tri.p[0]);
    line2 = vectorsub(tri.p[2], tri.p[0]);
    normal = vectorcrossprod(line1, line2);
    normal = vectornormal(normal);
    vcamray = vectorsub(tri.p[0], e->vlist.vcamera);
    if (vectorproduct(normal, vcamray) < 0)
    {
        lumiere(e, normal, color);
        return (1);
    }
    return (0);
}

void        rasterize_tri(t_env *env, t_mesh *obj)
{
    t_triangle  triproj;
    int         j;
    int         color;

    matrix_world(env, obj);
    j = -1;
    while (++j < obj->size)
    {
        triproj = obj->tris[j];
        pass_data(&triproj, obj->tris[j]);
        triproj.mesh_id = env->mesh_id;
        matrix_mult_triangle(env->mlist.matworld, &triproj);
        color = obj->color;
        if (normalize(env, triproj, &color) == 1)
            projection(env, triproj, color);
    }
}

void        engine_3d(t_env *env)
{
    int         i;
    t_thread    thread;
    t_triangle  triprojected;
    t_mesh      *obj;

    //do_camera rot/move
    matrix_view(env);
    if (env->obj_on_world == -1)
        return ;
    env->mesh_id = -1;
    i = -1;
    while (++i < env->obj_on_world)
    {
        env->mesh_id++;
        if (!(obj = (t_mesh*)ft_listfind(&env->world_obj, i)))
            ft_exit(env, "DooM: list find echec\n", 0);
        rasterize_tri(env, obj);
    }
    rasterizer(env, &env->to_clip);
    clear_dyntab(&env->to_clip);
}
