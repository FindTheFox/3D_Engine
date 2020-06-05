/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 19:22:01 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/06 01:08:44 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void     init_usr(t_env *e)
{
    int i;

    e->usr.platform = MENU;
    e->usr.mouse_ptr = 0;
    e->usr.draw_line = 0;
    e->usr.fill_text = 1;
    e->usr.forge = 1;
    e->usr.color = 1;
    e->usr.mouse_motion = 0;

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
    e->fAspectRatio = ((float)W_W / (float)W_H) - 1.1;
    e->fFovRad = 1.0f / tanf(e->fFov * 0.5 / 180 * 3.14159f);
    e->vlist.voff_set = (t_vec){ 1,1,1,1 };
    e->vlist.light_dir = (t_vec){ 5.0f, 10.0f, -5, 1 };
    e->yaw = 0;
    e->xaw = 0;
    e->zoom = 10;
    ft_bzero((void *)e->key, sizeof(char ) * KEY_NB);
    set_matrice(e);
    init_matrix_proj(e);
    init_dynamic_tab(e);
    if (!(e->depth_buff = ft_memalloc(sizeof(t_dbuff) * W_H * W_W))
    || !(e->pixel_buff = ft_memalloc(sizeof(int) * W_H * W_W)))
        ft_exit(e, "DooM: Engine Buffer init fail\n", 0);
    reset_pbuffer(e);
    init_usr(e);
}