/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/10 13:50:49 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void display_name(t_env *e, int x, int y, char *name)
{
	TTF_Font	*font;
	SDL_Surface *text;
	SDL_Color	color;
	SDL_Rect	pos;
	int ui_min;
	int i;


	ui_min = W_W - (W_W / 3);
	i = 0;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	if (!(font = TTF_OpenFont("./includes/assets/fonts/OpenSans-Regular.ttf", 15)))
		printf("%s\n", TTF_GetError());
	text = TTF_RenderText_Solid(font, name, color);
	pos.x = x;
	pos.y = y;
	SDL_BlitSurface(text, NULL, e->winsurf, &pos);
	TTF_CloseFont(font);
}

static void create_list(t_env *e)
{
	t_list *tmp;

	tmp = e->ed.selected;
	while (tmp)
	{
		if ((int)tmp->content_size == e->ed.mesh_choice)
			return ;
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", e->ed.meshd_tab[e->ed.mesh_choice].id);
	ft_lstadd(&e->ed.selected, tmp);
	tmp = e->ed.selected;
	while (tmp)
	{
		printf("%d\n", (int)tmp->content_size);
		tmp = tmp->next;
	}
	printf("################\n");
}

static void	mesh_choice(t_env *e)
{
	int j;
	int max;
	t_meshd meshd;
	int k;

	j = 0;
	max = 0;
	k = 0;
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
			if (e->ed.mesh_choice == 7 && compare_keyb(e, SDL_SCANCODE_DOWN))
			{
				if (e->ed.i < (e->ed.mesh_len % 7))
					e->ed.i++;
				j = e->ed.i;
				max = (e->ed.mesh_len % 7) - 1;
				while (j <= e->ed.i + 7 && e->ed.i <= max)
				{
					meshd.name = e->mesh[j].name;
					meshd.id = e->mesh[j].id;
					e->ed.meshd_tab[k] = meshd;
					j++;
					k++;
				}
			}
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
			if (e->ed.mesh_choice == 0)
			{
				if (e->ed.i == 0)
				{
					if (e->ed.mesh_len <= 8)
						e->ed.mesh_choice = e->ed.mesh_len - 1;
					else
						e->ed.mesh_choice = 7;
				}
				else
				{
					e->ed.i--;
					j = e->ed.i;
					k = 0;
					while (j <= e->ed.i + 7 && e->ed.i >= 0)
					{
						meshd.name = e->mesh[j].name;
						meshd.id = e->mesh[j].id;
						e->ed.meshd_tab[k] = meshd;
						j++;
						k++;
					}
				}
			}
		}
	}
	//	printf("%s && %d && choice == %d\n", e->ed.meshd_tab[e->ed.mesh_choice].name, e->ed.meshd_tab[e->ed.mesh_choice].id, e->ed.mesh_choice);
	//	printf("%d && choice == %d\n", e->ed.meshd_tab[e->ed.mesh_choice].id, e->ed.mesh_choice);
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
	int		i;
	int max;
	t_meshd	meshd;

	i = 0;
	if (e->ed.mesh_len > 8)
		max = 8;
	else
		max = e->ed.mesh_len;
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
	int ui_min;
	int i;

	i = 0;
	int pos;

	pos = 65;
	ui_min = W_W - (W_W / 3);
	draw_v(e);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)), 0xffffff);
	list_choice(e);
	e->ed.over_y = 65 + 30 * e->ed.mesh_choice;
	if (compare_keyb(e, SDL_SCANCODE_RETURN))
		e->ed.display = (e->l_choice == WEAPON) ? 1 : 0;
	if (e->ed.display)
	{
		display_list(e);
		mesh_choice(e);
		draw_area(e, e->ed.over_y, (ui_min + 50), 30, ((ui_min / 3)), 0xff00ff);
		while (i < 8)
		{
			display_name(e, (ui_min + 70), pos, e->ed.meshd_tab[i].name);
			pos = pos + 30;
			i++;
		}
		i = 0;
		if (compare_keyb(e, SDL_SCANCODE_SPACE))
			create_list(e);
	}
}

void editor(t_env *e)
{
	if (!e->ed.test)
		init_editor(e);
	editor_ui(e);
}
