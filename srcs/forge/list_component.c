/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_component.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Creatf. 2020/05/12 08:32:13 by brpinto           #+#    #+#             */
/*   Updatf. 2020/05/12 08:45:14 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void display_names(t_env *e, int x, int y, char *name)
{
	TTF_Font	*font;
	SDL_Surface	*text;
	SDL_Color	color;
	SDL_Rect	pos;
	int 		ui_min;
	int			i;


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


static void display_list(t_env *e)
{
	int		ui_min;
	int		list_h;
	int		i;
	int		max;
	t_meshd	meshd;

	i = 0;
	if (e->f.mesh_len > 8)
		max = 8;
	else
		max = e->f.mesh_len;
	if (e->f.mesh_len)
	{
		if (e->f.mesh_len <= 8)
			list_h = e->f.mesh_len * 30;
		else
			list_h = 8 * 30;
	}
	else
		list_h = 8 * 30;
	ui_min = W_W - (W_W / 3);
	draw_area(e, 65, (ui_min + 50), list_h, ((ui_min / 3)), 0xffffff);
}

void	draw_list_component(t_env *e)
{
	int	ui_min;
	int	i;
	int	pos;

	i = 0;
	pos = 65;
	ui_min = W_W - (W_W / 3);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)), 0xffffff);
	e->f.over_y = 65 + 30 * e->f.mesh_choice;
	if (e->f.display)
	{
		display_list(e);
		draw_area(e, e->f.over_y, (ui_min + 50), 30, ((ui_min / 3)), 0xff00ff);
		while (i < 8)
		{
			display_names(e, (ui_min + 70), pos, e->f.meshd_tab[i].name);
			pos = pos + 30;
			i++;
		}
		i = 0;
	}
}
