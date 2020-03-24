/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 23:16:57 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/22 23:18:04 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

float           distance_to_plane(t_vec plane_p, t_vec plane_n, t_vec p)
{
    float x;

    plane_n = vectornormal(plane_n); // p ou plane_n
    x = plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z;
    x -= vectorproduct(plane_n, plane_p);
    return (x);
}

// start 0 end 1

t_vec            vec_inter_plane(t_vec vec[2], t_vec linestart, t_vec lineend, float *t_out)
{
    float plane_d;
    float ad;
    float bd;
    float t;
    t_vec linestarttoend;
    t_vec linetointersect;

    vec[1] = vectornormal(vec[1]);
    plane_d = -vectorproduct(vec[1], vec[0]);
    // printf("plane_d %f\n", plane_d);
    ad = vectorproduct(linestart, vec[1]);
    bd = vectorproduct(lineend, vec[1]);
    t = (-plane_d - ad) / (bd - ad);
    *t_out = t;
    // printf("t_out %f \n", t);
    linestarttoend = vectorsub(lineend, linestart);
    linetointersect = vectormult(linestarttoend, t);
    return (vectoradd(linestart, linetointersect));
}