/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:26:33 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/12 09:06:30 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void create_list(t_env *e)
{
	t_list *tmp;

	tmp = e->f.selected;
	while (tmp)
	{
		if ((int)tmp->content_size == e->f.mesh_choice)
			return ;
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", e->f.meshd_tab[e->f.mesh_choice].id);
	ft_lstadd(&e->f.selected, tmp);
	tmp = e->f.selected;
	while (tmp)
	{
		printf("%d\n", (int)tmp->content_size);
		tmp = tmp->next;
	}
	printf("################\n");
}

void draw_area(t_env *e, int row_start, int col_start, int h, int w, Uint32 color)
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

void draw_v(t_env *e)
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
