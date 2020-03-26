/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:43:47 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

t_vec           vectordiv(t_vec v, float a)
{
    v.x /= a;
    v.y /= a;
    v.z /= a;
    return (v);
}

t_vec           vectormult(t_vec v, float a)
{   
    v.x *= a;
    v.y *= a;
    v.z *= a;
    return (v);
}

t_vec           vectoradd(t_vec v1, t_vec v2)
{
    t_vec v;

    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z; 
    return (v);
}

t_vec           vectorsub(t_vec v1, t_vec v2)
{
    t_vec v;

    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z; 
    v.x = v1.x - v2.x;
    return (v);
}

float           vectorproduct(t_vec v1, t_vec v2)
{
    return(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float           vectorlen(t_vec v)
{
    return (sqrtf(vectorproduct(v, v)));
}

t_vec           vectornormal(t_vec v)
{
    float len;
    t_vec vo;

    len = vectorlen(v);
    vo.x = v.x / len;
    vo.y = v.y / len;
    vo.z = v.z / len;
    return (vo);
}

t_vec           vectorcrossprod(t_vec v1, t_vec v2)
{
    t_vec v;

    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return (v);
}

t_vec           matrix_mult_vector(t_matrix m, t_vec i)
{
    t_vec o;

    o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + i.w * m.m[3][0];
    o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + i.w * m.m[3][1];
    o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + i.w * m.m[3][2];
    o.w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + i.w * m.m[3][3];
    return (o);
}

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