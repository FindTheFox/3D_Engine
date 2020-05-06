/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/06 21:10:07 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void	mesh_choice(t_env *e)
{
	if (compare_keyb(e, SDL_SCANCODE_DOWN))
	{
		if (e->ed.mesh_len <= 8)
		{
			if (e->ed.mesh_choice < e->ed.mesh_len - 1)
				e->ed.mesh_choice++;
			else
				e->ed.mesh_choice = 0;
		}
		else
		{
			if (e->ed.mesh_choice < 7)
				e->ed.mesh_choice++;
		}
	}
	if (compare_keyb(e, SDL_SCANCODE_UP))
	{
		if (e->ed.mesh_choice > 0)
			e->ed.mesh_choice--;
		else
		{
			if (e->ed.mesh_len <= 8)
				e->ed.mesh_choice = e->ed.mesh_len - 1;
			else
				e->ed.mesh_choice = 7;
		}
	}
	printf("%d\n", e->ed.mesh_choice);
}

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

static void draw_area(t_env *e, int row_start, int col_start, int h, int w, Uint32 color)
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
			put_pixel(e, x, y, color);
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

static void display_list(t_env *e)
{
	int		ui_min;
	int		list_h;
	t_mesh	*obj;
	char	*mesh_tab[8];
	int		i;
	
	while(i < e->ed.mesh_len)
	{
		mesh_tab[i] = e->mesh[i].name;
		i++;
	}
	i = 0;
	if (e->ed.mesh_len)
	{
		if (e->ed.mesh_len <= 8)
			list_h = e->ed.mesh_len * 30;
		else
			list_h = 8 * 30;
	}
	else
		list_h = 8 * 30;
	ui_min = W_W - (W_W / 3);
	draw_area(e, 65, (ui_min + 50), list_h, ((ui_min / 3)), 0xffffff);
}

static void	editor_ui(t_env *e)
{
//	SDL_Rect rect;
	int ui_min;
//	SDL_Surface *test;

	ui_min = W_W - (W_W / 3);
	draw_v(e);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)), 0xffffff);
	list_choice(e);
/*	test = IMG_Load("includes/assets/tiles/cursor.bmp");
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 720;*/
	e->ed.over_y = 65 + 30 * e->ed.mesh_choice;
	if (compare_keyb(e, SDL_SCANCODE_RETURN))
		e->ed.display = (e->l_choice == WEAPON) ? 1 : 0;
	if (e->ed.display)
	{
		display_list(e);
		mesh_choice(e);
		draw_area(e, e->ed.over_y, (ui_min + 50), 30, ((ui_min / 3)), 0xff00ff);
	}
}

void editor(t_env *e)
{
	if (!e->ed.test)
		init_editor(e);
	editor_ui(e);
}
