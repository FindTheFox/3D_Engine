/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:55:29 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/27 23:23:37 by user42           ###   ########.fr       */
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