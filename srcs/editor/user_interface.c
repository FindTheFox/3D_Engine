/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/03 15:59:08 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void	list_choice(t_env *e)
{
	if (compare_keyb(e, SDL_SCANCODE_TAB))
	{
		printf("l_choice = %d\n", e->l_choice);
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
	int ui_min;

	ui_min = W_W - (W_W / 3);
	draw_v(e);
	draw_area(e, 40, (ui_min + 40), 20, ((ui_min / 3)));
	list_choice(e);

}

void editor(t_env *e)
{
	printf("state = %d\n", e->state);
	init_editor(e);
	editor_ui(e);
}

void    state_route(t_env *e)
{
	if (e->state == FORGE)
		editor(e);
	if (e->state == GAME)
		printf("GAME\n");
	if (e->state == MENU)
		printf("MENU\n");
}
