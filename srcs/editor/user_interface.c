/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/08 20:27:09 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void	mesh_choice(t_env *e)
{
	int j;
	int max;
	t_meshd meshd;
	int k;

//	printf("################ mesh_choice ################\n");
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
				e->ed.i++;
				j = e->ed.i;
				max = (e->ed.mesh_len % 7) - 1;
/*				if (e->ed.mesh_len > e->ed.i + 7)
					max = e->ed.i + 7;
				else
					max = e->ed.mesh_len - e->ed.i;*/
				while (j <= e->ed.i + 7 && e->ed.i <= max)
				{
					meshd.name = e->mesh[j].name;
					meshd.id = e->mesh[j].id;
					e->ed.meshd_tab[k] = meshd;
//					printf("%d\n", e->ed.i);
					j++;
					k++;
				}
				printf("==============\n");
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
			if (e->ed.mesh_len <= 8)
				e->ed.mesh_choice = e->ed.mesh_len - 1;
			else
				e->ed.mesh_choice = 7;
		}
	}
	printf("%s && %d && choice == %d\n", e->ed.meshd_tab[e->ed.mesh_choice].name, e->ed.meshd_tab[e->ed.mesh_choice].id, e->ed.mesh_choice);
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

//	printf("################ display ################\n");
	i = 0;
	if (e->ed.mesh_len > 8)
		max = 8;
	else
		max = e->ed.mesh_len;
/*	if (!(e->ed.meshd_tab = (t_meshd *)malloc(sizeof(t_meshd) * e->ed.mesh_len - 1)))
		ft_exit(e, "Mesh info alloc error", 0);
	while(i < e->ed.mesh_len)
	{
		meshd.name = e->mesh[i].name;
		meshd.id = e->mesh[i].id;
		e->ed.meshd_tab[i] = meshd;
//		printf("%d\n", i);
		i++;
	}*/
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
	}
}

void editor(t_env *e)
{
	if (!e->ed.test)
		init_editor(e);
	editor_ui(e);
}
