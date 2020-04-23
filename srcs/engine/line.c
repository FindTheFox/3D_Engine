/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 05:05:29 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void		ft_line(t_env *env, t_vec v1, t_vec v2, int color)
{
	t_line line;

	if (abs((int)v2.x - (int)v1.x) >= abs((int)v2.y - (int)v1.y))
		line.lenght = abs((int)v2.x - (int)v1.x);
	else
		line.lenght = abs((int)v2.y - (int)v1.y);
	line.dx = (v2.x - v1.x) / line.lenght;
	line.dy = (v2.y - v1.y) / line.lenght;
	line.x = v1.x + 0.5;
	line.y = v1.y + 0.5;
	line.i = 1;
	while (line.i <= line.lenght
	&& line.x < W_W && line.y < W_H)
	{
		put_pixel(env, (int)line.x, (int)line.y, color);
		line.x += line.dx;
		line.y += line.dy;
		line.i++;
	}
}