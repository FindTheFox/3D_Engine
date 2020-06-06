/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:45:42 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/04 20:21:15 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

int         rgba_to_hex(SDL_Color rgba)
{
    return ((rgba.r * 256 * 256) + (rgba.g * 256) + rgba.b);
}

SDL_Color   hex_to_rgba(int c)
{
    SDL_Color rgba;

    rgba.r = c / (256 * 256);
	rgba.g = (c / 256) % 256;
	rgba.b = c % 256;
	return (rgba);
}

int         color_shading(int color, float shade)
{
    SDL_Color c;

    c = hex_to_rgba(color);
    c.r *= shade;
    c.g *= shade;
    c.b *= shade;
    return (rgba_to_hex(c));
}

int         colorset(t_env *e, int i)
{
	/*
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
	
	static int color[16] = {
		65536 * 66 + 256 * 30 + 15,
		65536 * 25 + 256 * 7 + 26,
		65536 * 9 + 256 * 1 + 47,
		65536 * 4 + 256 * 4 + 73,
		65536 * 0 + 256 * 7 + 100,
		65536 * 12 + 256 * 44 + 138,
		65536 * 24 + 256 * 82 + 177,
		65536 * 57 + 256 * 125 + 209,
		65536 * 134 + 256 * 181 + 229,
		65536 * 211 + 256 * 236 + 248,
		65536 * 241 + 256 * 233 + 191,
		65536 * 248 + 256 * 201 + 95,
		65536 * 255 + 256 * 170 + 0,
		65536 * 204 + 256 * 128 + 0,
		65536 * 153 + 256 * 87 + 0,
		65536 * 106 + 256 * 52 + 3};
	
	*/
	static int color[16] = {
		0xffffff,
		0xdfffff,
		0xbfffff,
		0xa0ffff,
		0x80ffff,
		0x60dfff,
		0x3fbfff,
		0x1f9fff,
		0x7efe,
		0x5edf,
		0x3fbf,
		0x1fa0,
		0x80,
		0x60,
		0x3f,
		0x1f};
	
/*
		static int color[16] = {
		0xb2123e,
		0xab1644,
		0xa41a4b,
		0x9d1e51,
		0x952258,
		0x8e265f,
		0x872b65,
		0x802f6c,
		0x783373,
		0x713779,
		0x6a3b80,
		0x633f86,
		0x5c438d,
		0x544794,
		0x4d4b9a,
		0x464fa1,
		};
	*/



	return (color[i % 16]);
}