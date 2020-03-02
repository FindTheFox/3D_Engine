/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 01:18:31 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/20 18:25:41 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static t_vec    center(t_vec *out)
{
        out->x *= 0.5f * W_W;
        out->y *= 0.5f * W_H;
        return(*out);
}

int       lumiere(t_env *e, t_vec normal)
{
    float dp;
    
    e->vlist.light_dir = vectornormal(e->vlist.light_dir);
    dp = vectorproduct(normal, e->vlist.light_dir);
    return (color_shading(0xffff00, dp));
}

void            matrix_world(t_env *e)
{
    init_matrix_rotz(&e->mlist.matrotz, e->ztheta * 0.5f);
    init_matrix_rotx(&e->mlist.matrotx, e->xtheta);
    init_matrix_roty(&e->mlist.matroty, e->ytheta * 0.8);
    init_matrix_translation(&e->mlist.mattranslate, 0.0f, 0.0f, e->zoom);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matroty, e->mlist.matrotx);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matworld, e->mlist.matrotz);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matworld, e->mlist.mattranslate);
}

void            matrix_view(t_env *e)
{
    t_matrix        matcam;
    t_matrix        camrot;
    t_vec           up;
    t_vec           target;

    e->vlist.lookdir = (t_vec){ 0,0,1,0 };
    up = (t_vec){ 0,-1,0,0 };
    target = (t_vec){ 0,0,1,0 };
    
    init_matrix_identity(&camrot);
    camrot = matrix_mult_matrix(e->mlist.camrotx, e->mlist.camroty);
    //printf("Lx = %f Ly = %f Lz = %f\n", e->vlist.lookdir.x, e->vlist.lookdir.x, e->vlist.lookdir.z);
    
    e->vlist.lookdir = matrix_mult_vector(camrot, target);
    target = vectoradd(e->vlist.vcamera, e->vlist.lookdir);
    
    //printf("tx = %f ty = %f tz = %f\n", e->vlist.target.x, e->vlist.target.x, e->vlist.target.z);
    up = matrix_mult_vector(camrot, up);
    
    pointatmatrix(&matcam, e->vlist.vcamera, target, up);
    quickinversematrix(&e->mlist.matview, matcam);
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

void            clipping(t_env *e, t_triangle tri)
{
    //printf("proj color %x\n", tri.color);
    fill_triangle(e, tri, tri.color);
    //draw_triangle(e, tri);
}

void        projection(t_env *env, t_triangle triprojected, int color)
{
    t_triangle tview;

    //printf("x1 = %f y1 = %f z1 = %f\n", triprojected.p[0].x, triprojected.p[0].y, triprojected.p[0].z);
    tview = matrix_mult_triangle(env->mlist.matview, triprojected);
    //printf("x = %f y = %f z = %f\n", tview.p[0].x, tview.p[0].y, tview.p[0].z);
    triprojected = matrix_mult_triangle(env->mlist.matproj, tview);
    triprojected.p[0] = vectordiv(triprojected.p[0], triprojected.p[0].w);
    triprojected.p[1] = vectordiv(triprojected.p[1], triprojected.p[1].w);
    triprojected.p[2] = vectordiv(triprojected.p[2], triprojected.p[2].w); 

    //Scale
    triprojected.p[0] = vectoradd(triprojected.p[0], env->vlist.voff_set);
    triprojected.p[1] = vectoradd(triprojected.p[1], env->vlist.voff_set);
    triprojected.p[2] = vectoradd(triprojected.p[2], env->vlist.voff_set);

    triprojected.p[0] = center(&triprojected.p[0]);
    triprojected.p[1] = center(&triprojected.p[1]);
    triprojected.p[2] = center(&triprojected.p[2]);
    triprojected.color = color;
                //***draw and rasterize
    clipping(env, triprojected);
    //env->buffer[j] = triprojected;
    //while (j--)
    //    clipping(env, env->buffer[j]);
}

void        engine_3d(t_env *env)
{
    int     i;
    int     j;
    t_triangle triprojected;
    int         color;
    
    //do_camera_rot
    matrix_view(env);
    i = -1;
    while (++i < env->nbmesh)
    {
        matrix_world(env);
        j = -1;
        while (++j < env->mesh[i].size)
        {
            //if (!(env->buffer = (t_triangle *)ft_memalloc(sizeof(t_triangle) * env->mesh[i].size)))
            //    ft_exit(env, "Triangle buffer malloc error", 0);
            triprojected = matrix_mult_triangle(env->mlist.matworld, env->mesh[i].tris[j]);
            //normalize
            if ((color = normalize(env, triprojected)))
                projection(env, triprojected, color);
        }
        //free((t_triangle *)env->buffer);
    }
    sdl_render(env);
}
