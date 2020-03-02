/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:45:42 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/20 17:22:14 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

int         rgba_to_hex(t_rgba rgba)
{
    /*
    int c;

    c = rgba.r << 24;
    c = rgba.g << 16;
    c = rgba.b << 8;
    c = rgba.a;
    return (c);*/
    return ((rgba.r * 256 * 256) + (rgba.g * 256) + rgba.b);
}

t_rgba      hex_to_rgba(int c)
{
    t_rgba rgba;

    /*
    rgba.r = c >> 24;
    rgba.g = c >> 16;
    rgba.b = c >> 8;
    rgba.a = c;
    return (rgba);*/
    rgba.r = c / (256 * 256);
	rgba.g = (c / 256) % 256;
	rgba.b = c % 256;
	return (rgba);
}
/*
int			rgba_to_hsv(int r, int g, int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

t_rgba		fill_rgb(int c)
{
	t_rgba rgb;

	rgb.r = c / (256 * 256);
	rgb.g = (c / 256) % 256;
	rgb.b = c % 256;
	return (rgb);
}
*/

int         color_shading(int color, float shade)
{
    t_rgba c;

    c = hex_to_rgba(color);
    c.r *= shade;
    c.g *= shade;
    c.b *= shade;
    return (rgba_to_hex(c));
}