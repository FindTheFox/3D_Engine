/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:46:17 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/10 20:44:04 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void         small_triangle(t_clip clip, t_triangle out[2], t_vec vec[2])
{
    float t;

    out[0].p[0] = clip.in[0];
    out[0].tx[0] = clip.tx_in[0];

    out[0].p[1] = vec_inter_plane(vec, clip.in[0], clip.out[0], &t);
    out[0].tx[1].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[1].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v;
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;
    
    out[0].p[2] = vec_inter_plane(vec, clip.in[0], clip.out[1], &t);
    out[0].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v;
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;
}

static void          quad_triangle(t_clip clip, t_triangle out[2], t_vec vec[2])
{
    float t;

    out[0].p[0] = clip.in[0];
    out[0].p[1] = clip.in[1];
    out[0].tx[0] = clip.tx_in[0];
    out[0].tx[1] = clip.tx_in[1];
    
    out[0].p[2] = vec_inter_plane(vec, clip.in[0], clip.out[0], &t);
    out[0].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[0].u) + clip.tx_in[0].u;
    out[0].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[0].v) + clip.tx_in[0].v; 
    out[0].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[0].w) + clip.tx_in[0].w;

    out[1].p[0] = clip.in[1];
    out[1].tx[0] = clip.tx_in[1];
    out[1].p[1] = out[0].p[2];
    out[1].tx[1] = out[0].tx[2];

    out[1].p[2] = vec_inter_plane(vec, clip.in[1], clip.out[0], &t);
    out[1].tx[2].u = t * (clip.tx_out[0].u - clip.tx_in[1].u) + clip.tx_in[1].u;
    out[1].tx[2].v = t * (clip.tx_out[0].v - clip.tx_in[1].v) + clip.tx_in[1].v; 
    out[1].tx[2].w = t * (clip.tx_out[0].w - clip.tx_in[1].w) + clip.tx_in[1].w;
}

int                 make_triangle_clipped(t_clip *clip, t_triangle out[2], t_vec vec[2], t_triangle in)
{
    float   t;
    
    if (clip->inside == 1 && clip->outside == 2)
    {
        out[0].color = in.color;//0x0000ff;
        small_triangle(*clip, out, vec);       
        return (1);
    }
    else if (clip->inside == 2 && clip->outside == 1)
    {
        out[0].color = in.color;//0xff0000;
        out[1].color = in.color;//0x00ff00;
        quad_triangle(*clip, out, vec);
        return (2);
    }
    return (0);
}

void        sort_triangle(t_clip *clip, t_triangle in)
{
    int i;

    i = 0;
    clip->inside = 0;
    clip->outside = 0;
    clip->tx_inside = 0;
    clip->tx_outside = 0;
    while (i < 3)
    {
        if (clip->d[i] >= 0)
        {
            clip->in[clip->inside++] = in.p[i];
            clip->tx_in[clip->tx_inside++] = in.tx[i];
        }
        else
        {
            clip->out[clip->outside++] = in.p[i];
            clip->tx_out[clip->tx_outside++] = in.tx[i];
        }
        i++;
    }
}

int         clip_triangle_by_plane(t_vec plane_p, t_vec plane_n, t_triangle in, t_triangle out[2])
{
    t_clip  clip;
    int     ret;
    
    plane_n = vectornormal(plane_n);

    clip.d[0] = vectorproduct(plane_n, in.p[0]) - vectorproduct(plane_n, plane_p);
    clip.d[1] = distance_to_plane(plane_p, plane_n, in.p[1]);
    clip.d[2] = distance_to_plane(plane_p, plane_n, in.p[2]);

    sort_triangle(&clip, in);
    if (clip.inside == 0)
        return (0);
    else if (clip.inside == 3)
    {
        out[0] = in;
        return (1);
    }
    else
    {
        ret = make_triangle_clipped(&clip, out, (t_vec[2]){plane_p, plane_n}, in);
        return(ret);
    }
}
