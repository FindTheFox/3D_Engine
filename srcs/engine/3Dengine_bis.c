/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3Dengine_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 19:53:03 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/12 15:22:21 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void       center(t_vec *out)
{
        out->x *= 0.5f * W_W;
        out->y *= 0.5f * W_H;
        //return(*out);
}

int         lumiere(t_env *e, t_vec normal)
{
    float dp;
 
    e->vlist.light_dir = vectornormal(e->vlist.light_dir);
    dp = vectorproduct(normal, e->vlist.light_dir);
    //return (color_shading(e->mesh[e->mesh_id].color, dp));
    return (color_shading(0xffffff, dp));
}

void        matrix_world(t_env *e, float xtheta, float ytheta, float ztheta)
{
    t_vec tmp;

    init_matrix_rotz(&e->mlist.matrotz, ztheta);
    init_matrix_rotx(&e->mlist.matrotx, xtheta);
    init_matrix_roty(&e->mlist.matroty, ytheta);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matroty, e->mlist.matrotx);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matworld, e->mlist.matrotz);
    
    tmp = vectoradd(e->mesh[e->mesh_id].dir, (t_vec){0.0f, 0.0f, e->zoom});
    init_matrix_translation(&e->mesh[e->mesh_id].mattrans, tmp);
    e->mlist.matworld = matrix_mult_matrix(e->mlist.matworld, e->mesh[e->mesh_id].mattrans);
}

void        matrix_view(t_env *e)
{
    t_matrix        matcam;
    t_matrix        camrot;
    t_vec           up;
    t_vec           target;

    e->vlist.lookdir = (t_vec){ 0,0,1,0 };
    up = (t_vec){ 0,-1,0,0 };
    target = (t_vec){ 0,0,1,0 };
 
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
