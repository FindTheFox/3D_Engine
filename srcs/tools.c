/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:55:29 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/05 20:53:20 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

void            printmatrix(t_matrix m)
{
    int i;
    int j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            printf("M[%d][%d]: %f\n", i, j, m.m[i][j]);
    }
}

void        swap_vec(t_vec *v1, t_vec *v2)
{
    ft_fswap(&v1->x, &v2->x);
    ft_fswap(&v1->y, &v2->y);    
    ft_fswap(&v1->z, &v2->z);    
}

void        reset_pbuffer(t_env *e)
{
    int x;

    x = 0;
    while (x < PX_NB - 4)
    {
        e->depth_buff[x].w = -100000;
        e->depth_buff[x + 1].w = -100000;
        e->depth_buff[x + 2].w = -100000;
        e->depth_buff[x + 3].w = -100000;
        x += 4;
    }
}

uint32_t		get_color(SDL_Surface *img, int x, int y)
{
    unsigned int    color;
    uint8_t         *p;

    //pixels = (unsigned int *)img->pixels;
    p = (uint8_t *)img->pixels + y * img->pitch
	    + x * img->format->BytesPerPixel;
    //color = pixels[x + y * W_W];
    return (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
}

void            pass_data(t_triangle *t1, t_triangle t2)
{
    t1->mesh_id = t2.mesh_id;
    t1->screen_pos = t2.screen_pos;
    t1->color = t2.color;
    t1->tex = t2.tex;
    t1->tri_id = t2.tri_id;
}