/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:45:42 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/26 16:54:58 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

int         rgba_to_hex(t_rgba rgba)
{
    return ((rgba.r * 256 * 256) + (rgba.g * 256) + rgba.b);
}

t_rgba      hex_to_rgba(int c)
{
    t_rgba rgba;

    rgba.r = c / (256 * 256);
	rgba.g = (c / 256) % 256;
	rgba.b = c % 256;
	return (rgba);
}

int         color_shading(int color, float shade)
{
    t_rgba c;

    c = hex_to_rgba(color);
    c.r *= shade;
    c.g *= shade;
    c.b *= shade;
    return (rgba_to_hex(c));
}

int         colorset(t_env *e, int i)
{
	static int color[16] = {
		0xff000e,
		0x0eff00,
		0x000eff,
		0xf0f000,
		0x00f0f0,
		0xf000f0,
		0xff9f7e,
		0xff8f7f,
		0xfe7e7f,
		0xee6f7f,
		0xde5e7f,
		0xce4f7f,
		0xbe3f7f,
		0xae2f7f,
		0x9d1f7f,
		0x8d0e7f};
	return (color[i]);
}