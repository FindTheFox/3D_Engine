/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dengine_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:53:03 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/08 02:25:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void       center(t_vec *out)
{
        //out->x += 1;
        //out->y += 1;
        out->x *= 0.5f * W_W;
        out->y *= 0.5f * W_H;
        //return(*out);
}

int         lumiere(t_thread *t, t_vec normal, int *color)
{
    float   dp;
    
    t->vlist.light_dir = vectornormal(t->vlist.light_dir);
    dp = (vectorproduct(normal, t->vlist.light_dir) + 1) / 2;
    //dp = vectorproduct(normal, e->vlist.light_dir);
    
    if (((t_env*)t->env)->usr.color)
        *color = color_shading(*color, dp);
    else
        *color = color_shading(0xffffff, dp);
}

void        matrix_world(t_thread *t, t_mesh *obj)
{
    t_vec tmp;

    init_matrix_rotz(&t->mlist.matrotz, obj->ztheta);
    init_matrix_rotx(&t->mlist.matrotx, obj->xtheta);
    init_matrix_roty(&t->mlist.matroty, obj->ytheta);
    t->mlist.matworld = matrix_mult_matrix(t->mlist.matroty, t->mlist.matrotx);
    t->mlist.matworld = matrix_mult_matrix(t->mlist.matworld, t->mlist.matrotz);
    
    tmp = vectoradd(obj->dir, (t_vec){2.0f, 0.0f, 10, 0});
    tmp = vectoradd(tmp, (t_vec){obj->id * 5,0,0,0});
    init_matrix_translation(&obj->mattrans, tmp);
    t->mlist.matworld = matrix_mult_matrix(t->mlist.matworld, obj->mattrans);
}

void        matrix_view(t_env *e)
{
    t_matrix        matcam;
    t_matrix        camrot;
    t_vec           up;
    t_vec           target;

    e->vlist.lookdir = (t_vec){ 0,0,1,1 };
    up = (t_vec){ 0,-1,0,1 };
    target = (t_vec){ 0,0,1,1 };
 
    init_matrix_roty(&e->mlist.camroty, ft_to_radian(e->yaw) * 15);
    init_matrix_rotx(&e->mlist.camrotx, ft_to_radian(e->xaw) * 9); 
    
    init_matrix_identity(&camrot);
    camrot = matrix_mult_matrix(e->mlist.camrotx, e->mlist.camroty);
    
    e->vlist.lookdir = matrix_mult_vector(camrot, target);
    target = vectoradd(e->vlist.vcamera, e->vlist.lookdir);
    
    up = matrix_mult_vector(camrot, up);
    
    pointatmatrix(&matcam, e->vlist.vcamera, target, up);
    quickinversematrix(&e->mlist.matview, matcam);
}
