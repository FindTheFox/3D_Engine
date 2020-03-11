/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:25:04 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/11 19:25:48 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

void        take_texture_vec(t_triangle *out, t_triangle in)
{
    out->tx[0].u = in.tx[0].u;
    out->tx[0].v = in.tx[0].v;
    out->tx[0].w = in.tx[0].w;

    out->tx[1].u = in.tx[1].u;
    out->tx[1].v = in.tx[1].v;
    out->tx[1].w = in.tx[1].w;

    out->tx[2].u = in.tx[2].u;
    out->tx[2].v = in.tx[2].v;
    out->tx[2].w = in.tx[2].w;
}