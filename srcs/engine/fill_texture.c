/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 00:59:09 by user42            #+#    #+#             */
/*   Updated: 2020/04/29 23:58:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

int			sample_pixel(SDL_Surface *s, t_vec2d px)
{
	int				ret;
	int				pos;
	unsigned int	*pixels;

	if (px.u < 0.0f || px.v < 0.0f || px.u > 1.0f || px.v > 1.0f)
		return (0);
	pixels = (unsigned int*)s->pixels;
	pos = (abs((int)((px.v * s->h) - 1))) * s->w;
	pos += (int)(px.u * s->w);
	ret = pixels[pos];
	return (ret);
}

static void	write_pixel(t_env *env, t_filltex *fill, t_triangle *t, int dist[3])
{
	SDL_Surface *sp;
	int			color;

	if (dist[2] <= PX_NB && fill->tex_w > env->depth_buff[dist[2]])
	{
		if (t->tex == 1 && (sp = env->mesh[env->mesh_id].img))
			color = get_pixel(sp, fill->tex_u / fill->tex_w, fill->tex_v / fill->tex_w);
		else
			color = t->color;
		env->depth_buff[dist[2]] = fill->tex_w;
		env->pixel_buff[dist[2]] = t->mesh_id;
		put_pixel_txt(env, dist[2], color);
	}
}

static void	compute_step(t_filltex *fill, float steps[6], float simples[6])
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

static void	refresh_step(float steps[6], float simples[6])
{
	simples[0] -= steps[0];
	simples[1] += steps[1];
	simples[2] -= steps[2];
	simples[3] += steps[3];
	simples[4] -= steps[4];
	simples[5] += steps[5];
}

static void	do_step(t_env *env, t_filltex *fill, t_triangle t, int i)
{
	int		j;
	int		dist;
	float	steps[6];
	float	simples[6];

	j = fill->ax;
	fill->tstep = 1.0f / (fill->bx - fill->ax);
	dist = j + abs(i - 1) * W_W;
	compute_step(fill, steps, simples);
	while (j < fill->bx)
	{
		if (t.tex)
		{
			fill->tex_u = simples[0] + simples[1];
			fill->tex_v = simples[2] + simples[3];
		}
		fill->tex_w = simples[4] + simples[5];
		refresh_step(steps, simples);
		if (dist < PX_NB)
			write_pixel(env, fill, &t, (int[3]){i, j, dist});
		dist++;
		j++;
	}
}

static void	fill_triangle_top(t_env *env, t_filltex *fill, t_triangle t)
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
		do_step(env, fill, t, i);
		i++;
	}
}

static void	fill_triangle_bot(t_env *env, t_filltex *fill, t_triangle t)
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
		do_step(env, fill, t, i);
		i++;
	}
}

void		fill_triangle_texture(t_env *env, t_triangle t)
{
	t_filltex	fill;

	//fill = (t_texturizer){};
	starting_swap(&t);
	compute_gradients(&fill, t, false);
	if (fill.dy1)
		fill_triangle_top(env, &fill, t);
	compute_gradients(&fill, t, true);
	if (fill.dy1)
		fill_triangle_bot(env, &fill, t);
}
