/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:22:01 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/28 22:56:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

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

static void     init_usr(t_env *e)
{
    int i;

    e->usr.platform = GAME;
    
    e->usr.f[0] = menu_start; //MENU
    e->usr.f[1] = gameplay;
    e->usr.f[2] = menu_pause;
    e->usr.f[3] = menu_option;
    e->usr.f[4] = forge;
}

void    init_data(t_env *e)
{
    e->fNear = 0.01f;
    e->fFar = 1000.0f;
    e->fFov = 80.0f;
    e->fAspectRatio = ((float)W_W / (float)W_H) - 0.9;
    e->fFovRad = 1.0f / tanf(e->fFov * 0.5 / 180 * 3.14159f);
    e->vlist.voff_set = (t_vec){ 1,1,1,1 };
    e->vlist.light_dir = (t_vec){ 5.0f, 10.0f, -5, 1 };
    //e->xtheta = 0;
    //e->ytheta = 0;
    //e->ztheta = 0;
    e->yaw = 0;
    e->xaw = 0;
    e->zoom = 10;
    ft_bzero((void *)e->key, sizeof(char ) * KEY_NB);
    init_matrice(e);
    init_matrix_proj(e);
    init_dynamic_tab(e);
    if (!(e->depth_buff = ft_memalloc(sizeof(float) * W_H * W_W)))
        ft_exit(e, "DooM: depth_buffer init fail\n", 0);
    reset_pbuffer(e);
    init_usr(e);
}