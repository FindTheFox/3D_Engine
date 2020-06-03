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

void display_name(t_env *e, int y, int x, char *name)
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

static void display_content(t_env *e, t_int start, t_button *button)
{
	int		list_h;
	int		i;
	int		max;
	int		pos;
	t_int	size;

	size.x = 300;
	pos = start.y + 35;
	i = 0;
	if (button->content.elem_num > 8)
		max = 8;
	else
		max = button->content.elem_num;
	if (e->f.mesh_len)
	{
		if (e->f.mesh_len <= 8)
			list_h = e->f.mesh_len * size.y;
		else
			list_h = 8 * size.y;
	}
	else
		list_h = 8 * size.y;
	size.y = 30 * max;
	draw_area(e, start.y + 35, start.x + 10, size, 0xffffff);
	size.y = 30;
	draw_area(e, e->f.over_y, (start.x + 10), size, 0xff00ff);
	while (i < max)
	{
		display_name(e, pos, start.x + 30, button->content.meshd_tab[i].name);
		pos = pos + 30;
		i++;
	}
}

void	draw_list_component(t_env *e, t_int start, t_int size, t_button *button)
{
//	Uint32 color;
//	draw_area(e, start.y, start.x, size, 0x0fffff);
//	display_name(e, start.y + 5, start.x + 5, title);
	e->f.over_y = (start.y + 35) + (size.y * e->f.mesh_choice);
//	if (e->f.display)
		display_content(e, start, button);
}
