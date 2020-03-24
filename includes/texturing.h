/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 23:43:35 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/23 05:04:01 by saneveu          ###   ########.fr       */
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
    int         dy1;
    int         dx1;
    float       du1;
    float       dv1;
    int         dy2;
    int         dx2;
    float       du2;
    float       dv2;
    float       dw1;
    float       dw2;
    float       dax_s;
    float       dbx_s;
    float       du1_s;
    float       du2_s;
    float       dv1_s;
    float       dv2_s;
    float       dw1_s;
    float       dw2_s;
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