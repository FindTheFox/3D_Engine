/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dengine.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:18:31 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/11 17:56:37 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        projection2(t_env *env, t_triangle tview, int color)
{
    t_triangle triprojected;

    triprojected = matrix_mult_triangle(env->mlist.matproj, tview);
    take_texture_vec(&triprojected, tview);
    triprojected.p[0] = vectordiv(triprojected.p[0], triprojected.p[0].w);
    triprojected.p[1] = vectordiv(triprojected.p[1], triprojected.p[1].w);
    triprojected.p[2] = vectordiv(triprojected.p[2], triprojected.p[2].w); 

    //Scale
    triprojected.p[0] = vectoradd(triprojected.p[0], env->vlist.voff_set);
    triprojected.p[1] = vectoradd(triprojected.p[1], env->vlist.voff_set);
    triprojected.p[2] = vectoradd(triprojected.p[2], env->vlist.voff_set);

    center(&triprojected.p[0]);
    center(&triprojected.p[1]);
    center(&triprojected.p[2]);
    
    triprojected.color = color;
    if (push_dynarray(&env->to_clip, &triprojected, false))
        ft_exit(env, "push dynamic tab to_clip fail", 0);
}

void        projection(t_env *env, t_triangle triprojected, int color)
{
    t_triangle  clip[2];
    t_triangle  tview;
    int         i;
    int         nclip;

    tview = matrix_mult_triangle(env->mlist.matview, triprojected);
    take_texture_vec(&tview, triprojected);
    tview.color = color;
    //clip z plane
    nclip = clip_triangle_by_plane((t_vec){0,0,0.5f,1.0f}, (t_vec){0,0,0.1,1.0f}, tview, clip);
    i = -1;
    while (++i < nclip)
        projection2(env, clip[i], color);
}

int        normalize(t_env *e, t_triangle tri)
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
        return (lumiere(e, normal));
    return (0);
}

void        engine_3d(t_env *env)
{
    int     i;
    int     j;
    t_triangle triprojected;
    int         color;

    //do_camera rot/move
    matrix_view(env);
    i = -1;
    while (++i < env->nbmesh)
    {
        env->mesh_id = i;
        //do mesh rot/move
        matrix_world(env, env->mesh[i].xtheta, env->mesh[i].ytheta, env->mesh[i].ztheta);
        j = -1;
        while (++j < env->mesh[i].size)
        {
            triprojected = matrix_mult_triangle(env->mlist.matworld, env->mesh[i].tris[j]);
            take_texture_vec(&triprojected, env->mesh[i].tris[j]);
            if ((color = normalize(env, triprojected)))
                projection(env, triprojected, color);
        }
    }
    rasterizer(env, &env->to_clip);
    clear_dynarray(&env->to_clip);
    sdl_render(env);
}
