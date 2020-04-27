/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 23:43:35 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/28 00:43:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURING_H
# define TEXTURING_H

# include "3d_engine.h"
# include "../libft/includes/libft.h"
//# include "../../includes/3dengine.h"

typedef struct      s_filltex
{
    //int x1;
    //int x2;
    //int x3;
    //int y1;
    //int y2;
    //int y3;
    //float u1;
    //float u2;
    //float u3;
    //float v1;
    //float v2;
    //float v3;
    float       simple[6];
    float       step[6];
    float       t;
    float       dy1;
    float       dx1;
    float       du1;
    float       dv1;
    float       dy2;
    float       dx2;
    float       du2;
    float       dv2;
    float       dw1;
    float       dw2;
    float       ax_s;
    float       bx_s;
    float       u1_s;
    float       u2_s;
    float       v1_s;
    float       v2_s;
    float       w1_s;
    float       w2_s;
    float       ax;
    float       bx;
    float       su;
    float       sv;
    float       sw;
    float       eu;
    float       ev;
    float       ew;
    float       tex_u;
    float       tex_v;
    float       tex_w;
    float       tstep;
}                   t_filltex;

#endif