/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:46:17 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/03 18:23:36 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

void        sort_triangle(t_clip *clip, t_triangle in)
{
    int i;

    i = 0;
    clip->inside = 0;
    clip->outside = 0;
    while (i < 3)
    {
        if (clip->d[i] >= 0)
        {
            clip->in[clip->inside++] = in.p[i];
        }
        else
        {
            clip->out[clip->outside++] = in.p[i];
        }
        i++;
    }
}

int         refactor_triangle(t_clip *clip, t_triangle out[2], t_vec vec[2], t_triangle in)
{

    if (clip->inside == 1 && clip->outside == 2)
    {
        out[0].color = in.color;
        out[0].p[0] = clip->in[0];
        out[0].p[1] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[0]);
        out[0].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[1]);
        return (1);
    }
    else if (clip->inside == 2 && clip->outside == 1)
    {
        out[0].color = in.color;
        out[1].color = in.color;
        
        out[0].p[0] = clip->in[0];
        out[0].p[1] = clip->in[1];
        out[0].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[0], clip->out[0]);

        out[1].p[0] = clip->in[1];
        out[1].p[1] = out[0].p[2];
        out[1].p[2] = vec_inter_plane(vec[0], vec[1], clip->in[1], clip->out[0]);
        return (2);
    }
    return (0);
}

int         clip_triangle(t_vec plane_n, t_vec plane_p, t_triangle in, t_triangle out[2])
{
    t_clip clip;

    plane_n = vectornormal(plane_n);
    clip.d[0] = distance_to_plane(plane_n, plane_p, in.p[0]);
    clip.d[1] = distance_to_plane(plane_n, plane_p, in.p[1]);
    clip.d[2] = distance_to_plane(plane_n, plane_p, in.p[2]);

    sort_triangle(&clip, in);
    if (clip.inside == 0)
        return (0);
    else if (clip.inside == 3)
    {
        out[0] = in;
        return (1);
    }
    else
        return (refactor_triangle(&clip, out, (t_vec[2]){plane_p, plane_n}, in));
}

void            raster_triangle(t_env *e, t_dyntab to_clip)
{
    
}