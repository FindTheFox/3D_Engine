/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:07:21 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static t_triangle       triangle_init(t_vec v0, t_vec v1, t_vec v2)
{
    t_triangle tri;

    tri.p[0] = v0;
    tri.p[1] = v1;
    tri.p[2] = v2;
    return (tri);
} 

static void            fill_tri_top(t_env *e, t_triangle tri, int color, t_fill fill)
{
    t_vec v0;
    t_vec v1;
    t_vec v2;
    int	    x;
    int	    y;

    v0 = tri.p[0];
    v1 = tri.p[1];
    v2 = tri.p[2];
    fill.m0 = (v2.x - v0.x) / (v2.y - v0.y);
    fill.m1 = (v2.x - v1.x) / (v2.y - v1.y);
    fill.ystart = (int)ceil(v0.y - 0.5f);
    fill.yend = (int)ceil(v2.y - 0.5f);
    y = fill.ystart - 1;
    while (++y < fill.yend)
    {
        fill.x0 = fill.m0 * (y + 0.5f - v0.y) + v0.x;
        fill.x1 = fill.m1 * (y + 0.5f - v1.y) + v1.x;
        fill.xstart = (int)(fill.x0 - 0.5f);
        fill.xend = (int)(fill.x1 - 0.5f);
		x = fill.xstart - 1;
        while (++x < fill.xend)
           put_pixel(e, x, y, color);

    }
}

static void            fill_tri_bot(t_env *e, t_triangle tri, int color, t_fill fill)
{
    t_vec v0;
    t_vec v1;
    t_vec v2;
    int     x;
    int     y;

    v0 = tri.p[0];
    v1 = tri.p[1];
    v2 = tri.p[2];
	fill.m0 = (v1.x - v0.x) / (v1.y - v0.y);
    fill.m1 = (v2.x - v0.x) / (v2.y - v0.y);
    fill.ystart = (int)ceil(v0.y - 0.5f);
    fill.yend = (int)ceil(v2.y - 0.5f);
	y = fill.ystart - 1;
    while (++y < fill.yend)
    {
        fill.x0 = fill.m0 * (y + 0.5f - v0.y) + v0.x;
        fill.x1 = fill.m1 * (y + 0.5f - v0.y) + v0.x;
        fill.xstart = (int)(fill.x0 - 0.5f);
        fill.xend = (int)(fill.x1 - 0.5f);
        x = fill.xstart - 1;
        while (++x < fill.xend)
            put_pixel(e, x, y, color);
    } 
}

static void            fill_both(t_env *e, t_triangle tri, int color, t_fill fill)
{
    float	alpha;
    t_vec	v0;
    t_vec	v1;
    t_vec	v2;
    t_vec	vi;

    v0 = tri.p[0];
    v1 = tri.p[1];
    v2 = tri.p[2];
    alpha = (v1.y - v0.y) / (v2.y - v0.y);
    vi.x = v0.x + (v2.x - v0.x) * alpha;
    vi.y = v0.y + (v2.y - v0.y) * alpha;
    vi.z = v0.z + (v2.z - v0.z) * alpha;
    if (v1.x < vi.x)
    {
        tri = triangle_init(v0, v1, vi);
        fill_tri_bot(e, tri, color, fill);
        tri = triangle_init(v1, vi, v2);
        fill_tri_top(e, tri, color, fill);
    }
    else
    {
        tri = triangle_init(v0, vi, v1);
        fill_tri_bot(e, tri, color, fill);
        tri = triangle_init(vi, v1, v2);
        fill_tri_top(e, tri, color, fill);
    } 
}

void            fill_triangle(t_env *e, t_triangle *tri, int color)
{
    t_vec       v0;
    t_vec       v1;
    t_vec       v2;
    t_triangle  triangle;
    t_fill      fill;

    ft_bzero((void*)&fill, sizeof(t_fill));
    v0 = tri->p[0];
    v1 = tri->p[1];
    v2 = tri->p[2];
    v1.y < v0.y ? ft_swap((void *)&v0, (void *)&v1) : 0;
    v2.y < v1.y ? ft_swap((void *)&v1, (void *)&v2) : 0;
    v1.y < v0.y ? ft_swap((void *)&v0, (void *)&v1) : 0;
    if (v0.y == v1.y)
    {
        v1.x < v0.x ? ft_swap((void *)&v0, (void *)&v1) : 0;
        triangle = triangle_init(v0, v1, v2);
        fill_tri_top(e, triangle, color, fill); 
    }
    else if (v1.y == v2.y)
    {
        v2.x < v1.x ? ft_swap((void *)&v1, (void *)&v2) : 0;
        triangle = triangle_init(v0, v1, v2);
        fill_tri_bot(e, triangle, color, fill);
    }
    else
    {
        triangle = triangle_init(v0, v1, v2);
        fill_both(e, triangle, color, fill);
    }
}