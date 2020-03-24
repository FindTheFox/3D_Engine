/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 23:43:47 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/22 23:20:09 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

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
