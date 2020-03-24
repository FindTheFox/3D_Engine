/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/22 23:19:18 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/22 23:20:07 by saneveu          ###   ########.fr       */
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
