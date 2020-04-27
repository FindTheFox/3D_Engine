/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_triangle_texture_bis.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 00:58:55 by user42            #+#    #+#             */
/*   Updated: 2020/04/28 00:58:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void	starting_swap(t_triangle *t)
{
	if (t->p[1].y < t->p[0].y)
	{
		ft_fswap(&t->p[0].y, &t->p[1].y);
		ft_fswap(&t->p[0].x, &t->p[1].x);
		t->tex ? ft_fswap(&t->tx[0].u, &t->tx[1].u) : 0;
		t->tex ? ft_fswap(&t->tx[0].v, &t->tx[1].v) : 0;
		ft_fswap(&t->tx[0].w, &t->tx[1].w);
	}
	if (t->p[2].y < t->p[0].y)
	{
		ft_fswap(&t->p[2].y, &t->p[0].y);
		ft_fswap(&t->p[2].x, &t->p[0].x);
		t->tex ? ft_fswap(&t->tx[2].u, &t->tx[0].u) : 0;
		t->tex ? ft_fswap(&t->tx[2].v, &t->tx[0].v) : 0;
		ft_fswap(&t->tx[2].w, &t->tx[0].w);
	}
	if (t->p[2].y < t->p[1].y)
	{
		ft_fswap(&t->p[2].y, &t->p[1].y);
		ft_fswap(&t->p[2].x, &t->p[1].x);
		t->tex ? ft_fswap(&t->tx[2].u, &t->tx[1].u) : 0;
		t->tex ? ft_fswap(&t->tx[2].v, &t->tx[1].v) : 0;
		ft_fswap(&t->tx[2].w, &t->tx[1].w);
	}
}

void	compute_steps(t_filltex *fill, bool t)
{
	if (fill->dy1)
	{
		fill->ax_s = fill->dx1 / fill->dy1;
		if (t)
			fill->u1_s = fill->du1 / fill->dy1;
		if (t)
			fill->v1_s = fill->dv1 / fill->dy1;
		fill->w1_s = fill->dw1 / fill->dy1;
	
	}
	if (fill->dy2)
	{
		fill->bx_s = fill->dx2 / fill->dy2;
		if (t)
			fill->u2_s = fill->du2 / fill->dy2;
		if (t)
			fill->v2_s = fill->dv2 / fill->dy2;
		fill->w2_s = fill->dw2 / fill->dy2;
	}
}

void	compute_gradients(t_filltex *fill, t_triangle t, bool flatbot)
{
	int		a;
	int		b;

	a = flatbot ? 2 : 1;
	b = flatbot ? 1 : 0;
	fill->dx1 = t.p[a].x - t.p[b].x;
	fill->dy1 = t.p[a].y - t.p[b].y;
	fill->du1 = t.tex ? t.tx[a].u - t.tx[b].u : 0;
	fill->dv1 = t.tex ? t.tx[a].v - t.tx[b].v : 0;
	fill->dw1 = t.tx[a].w - t.tx[b].w;

	if (!flatbot)
	{
		fill->dx2 = t.p[2].x - t.p[0].x;
		fill->dy2 = t.p[2].y - t.p[0].y;
		fill->du2 = t.tex ? t.tx[2].u - t.tx[0].u : 0;
		fill->dv2 = t.tex ? t.tx[2].v - t.tx[0].v : 0;
		fill->dw2 = t.tx[2].w - t.tx[0].w;
	}
	compute_steps(fill, t.tex);
}

void	set_line_bounds_top(t_filltex *fill, t_triangle t, float current)
{
	fill->ax = t.p[0].x + current * fill->ax_s;
	fill->bx = t.p[0].x + current * fill->bx_s;

	fill->su = t.tex ? t.tx[0].u + current * fill->u1_s : 0;
	fill->sv = t.tex ? t.tx[0].v + current * fill->v1_s : 0;
	fill->sw = t.tx[0].w + current * fill->w1_s;

	fill->eu = t.tex ? t.tx[0].u + current * fill->u2_s : 0;
	fill->ev = t.tex ? t.tx[0].v + current * fill->v2_s : 0;
	fill->ew = t.tx[0].w + current * fill->w2_s;

	if (fill->ax > fill->bx)
	{
		ft_fswap(&fill->ax, &fill->bx);
		t.tex ? ft_fswap(&fill->su, &fill->eu) : 0;
		t.tex ? ft_fswap(&fill->sv, &fill->ev) : 0;
		ft_fswap(&fill->sw, &fill->ew);
	}
}

void	set_line_bounds_bot(t_filltex *fill, t_triangle t, float currents[2])
{
	fill->ax = t.p[1].x + currents[1] * fill->ax_s;
	fill->bx = t.p[0].x + currents[0] * fill->bx_s;

	fill->su = t.tex ? t.tx[1].u + currents[1] * fill->u1_s : 0;
	fill->sv = t.tex ? t.tx[1].v + currents[1] * fill->v1_s : 0;
	fill->sw = t.tx[1].w + currents[1] * fill->w1_s;

	fill->eu = t.tex ? t.tx[0].u + currents[0] * fill->u2_s : 0;
	fill->ev = t.tex ? t.tx[0].v + currents[0] * fill->v2_s : 0;
	fill->ew = t.tx[0].w + currents[0] * fill->w2_s;

	if (fill->ax > fill->bx)
	{
		ft_fswap(&fill->ax, &fill->bx);
		t.tex ? ft_fswap(&fill->su, &fill->eu) : 0;
		t.tex ? ft_fswap(&fill->sv, &fill->ev) : 0;
		ft_fswap(&fill->sw, &fill->ew);
	}
}
