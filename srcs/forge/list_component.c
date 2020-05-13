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
	int			i;

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

static void display_content(t_env *e, t_int start, t_int size, int len)
{
	int		list_h;
	int		i;
	int		max;
	int		pos;

	pos = start.y + 35;
	i = 0;
	if (len > 8)
		max = 8;
	else
		max = len;
	if (e->f.mesh_len)
	{
		if (e->f.mesh_len <= 8)
			list_h = e->f.mesh_len * size.y;
		else
			list_h = 8 * size.y;
	}
	else
		list_h = 8 * size.y;
	draw_area(e, start.y + 35, start.x + 10, list_h, size.x, 0xffffff);
	draw_area(e, e->f.over_y, (start.x + 10), size.y, size.x, 0xff00ff);
	while (i < max)
	{
		display_names(e, start.x + 30, pos, e->f.meshd_tab[i].name);
		pos = pos + 30;
		i++;
	}
}

void	draw_list_component(t_env *e, t_int start, t_int size, int len)
{
	draw_area(e, start.y, start.x, size.y, size.x, 0xffffff);
	e->f.over_y = (start.y + 35) + (size.y * e->f.mesh_choice);
	if (e->f.display)
		display_content(e, start, size, len);
}
