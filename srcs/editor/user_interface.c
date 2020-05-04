/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/04 21:35:42 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void	list_choice(t_env *e)
{
	if (compare_keyb(e, SDL_SCANCODE_TAB))
	{
		if (e->l_choice < ROOM)
			e->l_choice++;
		else
			e->l_choice = 0;
	}
}

static void draw_area(t_env *e, int row_start, int col_start, int h, int w)
{
	int x;
	int y;

	y = row_start;
	x = col_start;
	while (y <= row_start + h)
	{
		x = (col_start);
		while (x <= (col_start + w))
		{
			put_pixel(e, x, y, 0xffffff);
			x++;
		}
		y++;
	}
}

static void draw_v(t_env *e)
{
	int i;
	int ui_min;

	i = 0;
	ui_min =  W_W - (W_W / 3);
	while (i <= W_H)
	{
		put_pixel(e, ui_min, i, 0xffffff);
		i++;
	}
}

static void	editor_ui(t_env *e)
{
	SDL_Rect rect;
	int ui_min;
	SDL_Surface *test;

	ui_min = W_W - (W_W / 3);
	draw_v(e);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)));
	list_choice(e);
	test = IMG_Load("includes/assets/tiles/cursor.bmp");
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 720;
	if (compare_keyb(e, SDL_SCANCODE_RETURN))
		e->ed.display = (e->l_choice == WEAPON) ? 1 : 0;
	if (e->ed.display)
		SDL_BlitSurface(test, NULL, e->winsurf, &rect);
}

void editor(t_env *e)
{
	init_editor(e);
	editor_ui(e);
}
