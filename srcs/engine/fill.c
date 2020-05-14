/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:07:21 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/28 00:27:22 by user42           ###   ########.fr       */
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

static float	vec3d_edge(t_vec a, t_vec b, t_vec c)
{
	return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x));
}

static t_vec	calc_w(t_triangle t, int data[3])
{
	float	area;
	t_vec	ret;
	t_vec	pixel;

	area = vec3d_edge(t.p[0], t.p[1], t.p[2]);
	pixel = (t_vec){data[0], data[1], 0, 0};
	ret = (t_vec){
		vec3d_edge(t.p[1], t.p[2], pixel) / area,
		vec3d_edge(t.p[2], t.p[0], pixel) / area,
		vec3d_edge(t.p[0], t.p[1], pixel) / area, 0};
	return (ret);
}
/*
void             draw_solo(t_env *e, t_triangle tri, t_fill fill, int data[3])
{
    t_vec	v;
	int		p;
    float   w;

	v = calc_w(tri, data);
	p = (data[0] - 1) + (data[1] - 1) * W_W;
    //printf("w0: %f      w1: %f      w2: %f\n", tri.tx[0].w, tri.tx[1].w, tri.tx[2].w);
	w = 1.0f / ((tri.tx[0].w * v.x) + (tri.tx[1].w * v.y) + (tri.tx[2].w * v.z));
    if (p >= 0 && p < PX_NB)
    {
        //printf("W: %f       P: %d\n", w, p);
        //printf("buff: %f\n", e->depth_buff[p]);
	    if (w <= e->depth_buff[p])
	    {
            //printf("IN\n");
            put_pixel(e, data[0], data[1], data[2]);
	    	e->depth_buff[p] = w;
	    	//draw_pixel(e->mlx.img_data, px.x, px.y, t.color);
	    }
    }
    //printf("X: %d   Y: %d   COLOR: %x\n", data[0], data[1], data[2]);
	//fill->tx += fill->xstep;
}
*/
static void             fill_tri_top(t_env *e, t_triangle *tri, int color, t_fill fill)
{
    t_vec v0;
    t_vec v1;
    t_vec v2;
    int	    x;
    int	    y;

    v0 = tri->p[0];
    v1 = tri->p[1];
    v2 = tri->p[2];
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
            //draw_solo(e, *tri, fill, (int[3]){x, y, color});

    }
}

static void            fill_tri_bot(t_env *e, t_triangle *tri, int color, t_fill fill)
{
    t_vec v0;
    t_vec v1;
    t_vec v2;
    int     x;
    int     y;

    v0 = tri->p[0];
    v1 = tri->p[1];
    v2 = tri->p[2];
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
            //draw_solo(e, *tri, fill, (int[3]){x, y, color});
    } 
}

static void            fill_both(t_env *e, t_triangle *tri, int color, t_fill fill)
{
    float	alpha;
    t_vec	v0;
    t_vec	v1;
    t_vec	v2;
    t_vec	vi;

    v0 = tri->p[0];
    v1 = tri->p[1];
    v2 = tri->p[2];
    alpha = (v1.y - v0.y) / (v2.y - v0.y);
    vi.x = v0.x + (v2.x - v0.x) * alpha;
    vi.y = v0.y + (v2.y - v0.y) * alpha;
    vi.z = v0.z + (v2.z - v0.z) * alpha;
    if (v1.x < vi.x)
    {
        *tri = triangle_init(v0, v1, vi);
        fill_tri_bot(e, tri, color, fill);
        *tri = triangle_init(v1, vi, v2);
        fill_tri_top(e, tri, color, fill);
    }
    else
    {
        *tri = triangle_init(v0, vi, v1);
        fill_tri_bot(e, tri, color, fill);
        *tri = triangle_init(vi, v1, v2);
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
    v1.y < v0.y ? swap_vec(&v0, &v1) : 0;
    v2.y < v1.y ? swap_vec(&v1, &v2) : 0;
    v1.y < v0.y ? swap_vec(&v0, &v1) : 0;
    if (v0.y == v1.y)
    {
        v1.x < v0.x ? swap_vec(&v0, &v1) : 0;
        triangle = triangle_init(v0, v1, v2);
        take_texture_vec(&triangle, *tri);
        //printf("w1: %f, w2: %f, w3: %f\n", triangle.tx[0].w, triangle.tx[1].w, triangle.tx[2].w);
        fill_tri_top(e, &triangle, color, fill); 
    }
    else if (v1.y == v2.y)
    {
        v2.x < v1.x ? swap_vec(&v1, &v2) : 0;
        triangle = triangle_init(v0, v1, v2);
        take_texture_vec(&triangle, *tri);
        //printf("w1: %f, w2: %f, w3: %f\n", triangle.tx[0].w, triangle.tx[1].w, triangle.tx[2].w);
        fill_tri_bot(e, &triangle, color, fill);
    }
    else
    {
        triangle = triangle_init(v0, v1, v2);
        take_texture_vec(&triangle, *tri);
        //printf("w1: %f, w2: %f, w3: %f\n", triangle.tx[0].w, triangle.tx[1].w, triangle.tx[2].w);
        fill_both(e, &triangle, color, fill);
    }
}