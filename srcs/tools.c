/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:55:29 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/29 22:14:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

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
        e->depth_buff[x] = -INFINITY;
        e->depth_buff[x + 1] = -INFINITY;
        e->depth_buff[x + 2] = -INFINITY;
        e->depth_buff[x + 3] = -INFINITY;
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
}