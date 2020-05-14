/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 22:27:35 by user42            #+#    #+#             */
/*   Updated: 2020/04/28 00:22:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3d_engine.h"

void	starting_swap(t_triangle *t)
{
	if (t->p[1].y < t->p[0].y)
	{
	    ft_fswap(&t->p[0].y, &t->p[1].y);
	    ft_fswap(&t->p[0].x, &t->p[1].x);
	    ft_fswap(&t->tx[0].u, &t->tx[1].u);
	    ft_fswap(&t->tx[0].v, &t->tx[1].v);
	    ft_fswap(&t->tx[0].w, &t->tx[1].w);
	}
	if (t->p[2].y < t->p[0].y)
	{
		ft_fswap(&t->p[2].y, &t->p[0].y);
		ft_fswap(&t->p[2].x, &t->p[0].x);
		ft_fswap(&t->tx[2].u, &t->tx[0].u);
		ft_fswap(&t->tx[2].v, &t->tx[0].v);
		ft_fswap(&t->tx[2].w, &t->tx[0].w);
	}
	if (t->p[2].y < t->p[1].y)
	{
		ft_fswap(&t->p[2].y, &t->p[1].y);
		ft_fswap(&t->p[2].x, &t->p[1].x);
		ft_fswap(&t->tx[2].u, &t->tx[1].u);
		ft_fswap(&t->tx[2].v, &t->tx[1].v);
		ft_fswap(&t->tx[2].w, &t->tx[1].w);
	}
}

void	compute_steps(t_filltex *fill, int t)
{
	if (fill->dy1)
	{
		fill->ax_s = fill->dx1 / fill->dy1;
		//if (t)
			fill->u1_s = fill->du1 / fill->dy1;
		//if (t)
			fill->v1_s = fill->dv1 / fill->dy1;
		fill->w1_s = fill->dw1 / fill->dy1;
	
	}
	if (fill->dy2)
	{
		fill->bx_s = fill->dx2 / fill->dy2;
		//if (t)
			fill->u2_s = fill->du2 / fill->dy2;
		//if (t)
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
	fill->du1 = t.tx[a].u - t.tx[b].u;
	fill->dv1 = t.tx[a].v - t.tx[b].v;
	fill->dw1 = t.tx[a].w - t.tx[b].w;

	if (!flatbot)
	{
		fill->dx2 = t.p[2].x - t.p[0].x;
		fill->dy2 = t.p[2].y - t.p[0].y;
		fill->du2 = t.tx[2].u - t.tx[0].u;
		fill->dv2 = t.tx[2].v - t.tx[0].v;
		fill->dw2 = t.tx[2].w - t.tx[0].w;
	}
	compute_steps(fill, 0);
}

void	set_line_bounds_top(t_filltex *fill, t_triangle t, float current)
{
	fill->ax = t.p[0].x + current * fill->ax;
	fill->bx = t.p[0].x + current * fill->bx;

	fill->su = t.tx[0].u + current * fill->u1_s;
	fill->sv = t.tx[0].v + current * fill->v1_s;
	fill->sw = t.tx[0].w + current * fill->w1_s;

	fill->eu = t.tx[0].u + current * fill->u2_s;
	fill->ev = t.tx[0].v + current * fill->v2_s;
	fill->ew = t.tx[0].w + current * fill->w2_s;

	if (fill->ax > fill->bx)
	{
		swap_floats(&fill->ax, &fill->bx);
		swap_floats(&fill->su, &fill->eu);
		swap_floats(&fill->sv, &fill->ev);
		swap_floats(&fill->sw, &fill->ew);
	}
}

void	set_line_bounds_bot(t_filltex *fill, t_triangle t, float currents[2])
{
	fill->ax = t.p[1].x + currents[1] * fill->ax_s;
	fill->bx = t.p[0].x + currents[0] * fill->bx_s;

	fill->su = t.tx[1].u + currents[1] * fill->u1_s;
	fill->sv = t.tx[1].v + currents[1] * fill->v1_s;
	fill->sw = t.tx[1].w + currents[1] * fill->w1_s;
    fill->eu = t.tx[0].u + currents[0] * fill->u2_s;
	fill->ev = t.tx[0].v + currents[0] * fill->v2_s;
	fill->ew = t.tx[0].w + currents[0] * fill->w2_s;

	if (fill->ax > fill->bx)
	{
		ft_fswap(&fill->ax, &fill->bx);
		ft_fswap(&fill->su, &fill->eu);
		ft_fswap(&fill->sv, &fill->ev);
		ft_fswap(&fill->sw, &fill->ew);
	}
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int			sample_pixel(char *img, int i, int j, t_vec2d point)
{
	int		ret;
	int		pos;

	if (point.u < 0.0f || point.v < 0.0f || point.u > 1.0f || point.v > 1.0f)
		return (0);
	pos = (abs((int)((point.v * j) - 1))) * i;
	pos += (int)(point.u * i);
	pos *= 4;
	ret = *(int*)(&img[pos]);
	return (ret);
}

static void	write_pixel(t_env *env, t_filltex *fill, t_triangle t, int pos[3])
{
	//t_sprite	*sp;
	float		cu;
	float		cv;
	int			color;

	if (pos[2] <= env->data.data_size/* && txt->txt_w > env->cam.z_buffer[pos[2]]*/)
	{
		//if (t.sp >= 0 && t.textured)
		//{
		//	sp = dyacc(&env->maps[env->scene].txts, t.sp);
			cu = fill->tex_u / fill->tex_w;
			cv = fill->tex_v / fill->tex_w;
			color = sample_pixel(sp->img_data, sp->hgt, sp->wdt}, (t_vec2d){cu, cv, 1.0f});
			color = shade_color(color, t.illum);
		}
		else
			color = t.color;
		env->cam.z_buffer[pos[2]] = txt->txt_w;
		*(int*)(&env->mlx.img_data[pos[2] * 4]) = color;
	}
}

static void	simplify_interpolation(t_filltex *fill, float steps[6], float simples[6])
{
	steps[0] = (fill->tstep * fill->su);
	steps[1] = (fill->tstep * fill->eu);
	steps[2] = (fill->tstep * fill->sv);
	steps[3] = (fill->tstep * fill->ev);
	steps[4] = (fill->tstep * fill->sw);
	steps[5] = (fill->tstep * fill->ew);
	simples[0] = fill->su;
	simples[1] = 0.0f;
	simples[2] = fill->sv;
	simples[3] = 0.0f;
	simples[4] = fill->sw;
	simples[5] = 0.0f;
}

static void	update_expr(float steps[6], float simples[6])
{
	simples[0] -= steps[0];
	simples[1] += steps[1];
	simples[2] -= steps[2];
	simples[3] += steps[3];
	simples[4] -= steps[4];
	simples[5] += steps[5];
}

static void	draw_triangle_line(t_env *env, t_filltex *fill, t_triangle t, int i)
{
	int		j;
	int		px;
	float	steps[6];
	float	simples[6];

	j = fill->ax;
	fill->tstep = 1.0f / (fill->bx - fill->ax);
	px = abs(i - 1) * W_W + j;
	simplify_interpolation(fill, steps, simples);
	while (j < fill->bx)
	{
		//if (t.textured)
		//{
			fill->tex_u = simples[0] + simples[1];
			fill->tex_v = simples[2] + simples[3];
		//}
		fill->tex_w = simples[4] + simples[5];
		update_expr(steps, simples);
		write_pixel(env, fill, t, (int[3]){i, j, px});
		px++;
		j++;
	}
}

static void	flattop(t_env *env, t_filltex *fill, t_triangle t)
{
	int		i;
	int		end;

	i = ceil(t.p[0].y);
	end = ceil(t.p[1].y);
	while (i < end)
	{
		set_line_bounds_top(fill, t, i - t.p[0].y);
		fill->tex_u = fill->su;
		fill->tex_v = fill->sv;
		fill->tex_w = fill->sw;
		draw_triangle_line(env, fill, t, i);
		i++;
	}
}

static void	flatbot(t_env *env, t_filltex *fill, t_triangle t)
{
	int		i;
	int		end;

	i = ceil(t.p[1].y);
	end = ceil(t.p[2].y);
	while (i < end)
	{
		set_line_bounds_bot(fill, t, (float[2]){i - t.p[0].y, i - t.p[1].y});
		fill->tex_u = fill->su;
		fill->tex_v = fill->sv;
		fill->tex_w = fill->sw;
		draw_triangle_line(env, fill, t, i);
		i++;
	}
}

void		fill_triangle_texture(t_env *env, t_triangle t)
{
	t_filltex	fill;

    
	starting_swap(&t);
	compute_gradients(&fill, t, false);
	if (fill.dy1)
		flattop(env, &fill, t);
	compute_gradients(&fill, t, true);
	if (fill.dy1)
		flatbot(env, &fill, t);
}