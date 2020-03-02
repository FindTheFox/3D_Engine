/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:43:47 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:22:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

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

    len = vectorlen(v);
    v.x /= len;
    v.y /= len;
    v.z /= len;
    return (v);
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
