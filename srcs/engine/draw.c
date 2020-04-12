/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:33:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/10 21:18:00 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        put_pixel(t_env *e, int x, int y, int color)
{
    unsigned int     *pixels;

    if (x < 0 || x >= W_W || y < 0 || y > W_H)
        return ;
    pixels = (unsigned int *)e->winsurf->pixels;
    pixels[x + y * W_W] = color;
}

uint32_t		get_pixel(SDL_Surface *img, float tx, float ty)
{
	uint8_t			*p;

	p = (uint8_t *)img->pixels + (int)(ty * img->h) * img->pitch
	    + (int)(tx * img->w) * img->format->BytesPerPixel;
	return (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
}

void        draw_triangle(t_env *e, t_triangle t)
{
    ft_line(e, t.p[0], t.p[1], 0xffffff);
    ft_line(e, t.p[0], t.p[2], 0xffffff);
    ft_line(e, t.p[1], t.p[2], 0xffffff);
}

void        sdl_render(t_env *e)
{
    int i;
    unsigned int *pixels;

    e->screen = SDL_CreateTextureFromSurface(e->rend, e->winsurf);
    SDL_RenderCopy(e->rend, e->screen, NULL, NULL);
    SDL_RenderPresent(e->rend);
    SDL_DestroyTexture(e->screen);
    pixels = (unsigned int *)e->winsurf->pixels;
    i = -1;
    while (++i < W_W * W_H)
        pixels[i] = (0 | 0 << 8 | 0 << 16 | 255 << 24);
    //SDL_SetRenderDrawColor(e->rend, 0, 0, 0, 0);
    //SDL_RenderClear(e->rend);
}