/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:22:01 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/20 18:15:10 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static void     init_matrice(t_env *e)
{
    int i;

    i = 0;
    while (i < 4)
    {
        ft_memset(&e->mlist.camrotx.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.camroty.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matworld.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matview.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.mattranslate.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matrotx.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matroty.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matrotz.m[i][0], 0, sizeof(float) * 4);
        ft_memset(&e->mlist.matproj.m[i][0], 0, sizeof(float) * 4);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        e->mlist.camrotx.m[i][i] = 1.0f;
        e->mlist.camroty.m[i][i] = 1.0f;
        e->mlist.matworld.m[i][i] = 1.0f;
        e->mlist.matview.m[i][i] = 1.0f;
        e->mlist.mattranslate.m[i][i] = 1.0f;
        e->mlist.matrotx.m[i][i] = 1.0f;
        e->mlist.matroty.m[i][i] = 1.0f;
        e->mlist.matrotz.m[i][i] = 1.0f;
        e->mlist.matproj.m[i][i] = 1.0f;
        i++;
    }

}

void    init_data(t_env *e)
{
    e->fNear = 0.1f;
    e->fFar = 1000.0f;
    e->fFov = 90.0f;
    e->fAspectRatio = (float)W_W / (float)W_H;
    e->fFovRad = 1.0f / tanf(e->fFov * 0.5 / 180 * 3.14159f);
    e->vlist.voff_set = (t_vec){ 1,1,1,1 };
    e->vlist.light_dir = (t_vec){ 0.0f, 0.0f, -1.0f, 0.0f };
    e->xtheta = 0;
    e->ytheta = 0;
    e->ztheta = 0;
    e->yaw = 0;
    e->xaw = 0;
    e->zoom = 20;
    ft_bzero((void *)e->key, sizeof(char ) * KEY_NB);
    init_matrice(e);
    init_matrix_rotx(&e->mlist.matrotx, e->xtheta);
    init_matrix_roty(&e->mlist.matroty, e->ytheta);
    init_matrix_rotz(&e->mlist.matrotz, e->ztheta);
    init_matrix_proj(e);
    init_matrix_translation(&e->mlist.mattranslate, 0, 0, e->zoom);
}