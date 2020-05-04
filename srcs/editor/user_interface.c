/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/04 14:56:42 by brpinto          ###   ########.fr       */
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

static SDL_Texture	*init_texture(t_env *e, char *path)
{
	SDL_Texture		*texture;
	SDL_Surface		*surface;

	texture = NULL;
	if (!(surface = SDL_LoadBMP(path)))
		return (NULL);
	if (!(texture = SDL_CreateTextureFromSurface(e->rend, surface)))
		return (NULL);
	SDL_FreeSurface(surface);
	return (texture);
}

/*void                    load_textures(t_env *e)
{
	e->menu.bg_texture = init_texture(e, "./images/menu.bmp");
	e->menu.cursor_texture = init_texture(e, "./images/cursor.bmp");
	e->tex.s_wall_texture = init_texture(e, "./images/s.bmp");
	e->tex.n_wall_texture = init_texture(e, "./images/n.bmp");
	e->tex.e_wall_texture = init_texture(e, "./images/e.bmp");
	e->tex.o_wall_texture = init_texture(e, "./images/o.bmp");
	e->tex.end_texture = init_texture(e, "./images/end.bmp");
}*/

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
	int ui_min;
	SDL_Texture *test_tex;

	ui_min = W_W - (W_W / 3);
	draw_v(e);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)));
	list_choice(e);
	test_tex = init_texture(e, "../../debian.bmp");
	if (compare_keyb(e, SDL_SCANCODE_RETURN))
		(e->l_choice == WEAPON && e->state == FORGE) ? printf("weapon\n") : 0;
}

void editor(t_env *e)
{
	init_editor(e);
	editor_ui(e);
}
