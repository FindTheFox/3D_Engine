/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 01:58:51 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:22:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static void		draw_horizontal(t_env *e, t_vec p1, t_vec p2, int c)
{
	int			x;
	int			y;

	if (p1.x > p2.x)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.x + e->line.i <= p2.x)
	{
		x = p1.x + e->line.i;
		y = (int)(p1.y + e->line.i * e->line.coef);
		put_pixel(e, x, y, c);
		++e->line.i;
	}
}

static void		draw_vertical(t_env *e, t_vec p1, t_vec p2, int c)
{
	int			x;
	int			y;

	e->line.coef = 1 / e->line.coef;
	if (p1.y > p2.y)
		ft_swap((void *)&p1, (void *)&p2);
	while (p1.y + e->line.i <= p2.y)
	{
		x = (int)(p1.x + e->line.i * e->line.coef);
		y = p1.y + e->line.i;
		put_pixel(e, x, y, c);
		++e->line.i;
	}
}

void			draw_line(t_env *e, t_vec v1, t_vec v2, int color)
{
	e->line.i = 0;
	if (v2.x == v1.x)
		e->line.coef = 1000000;
	else
		e->line.coef = (double)(v2.y - v1.y) / (double)(v2.x - v1.x);
	if (e->line.coef > -1 && e->line.coef < 1)
		draw_horizontal(e, v1, v2, color);
	else
		draw_vertical(e, v1, v2, color);
}