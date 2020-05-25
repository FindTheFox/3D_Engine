/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:26:33 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/24 16:06:53 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

/*void create_list(t_env *e, void needle, void source, t_list list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
	{
		if ((int)tmp->content_size == e->f.meshd_tab[e->f.mesh_choice].id)
			return ;
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", e->f.meshd_tab[e->f.mesh_choice].id);
	ft_lstadd(&e->f.selected, tmp);
	tmp = list;
	while (tmp)
	{
		printf("%d\n", (int)tmp->content_size);
		tmp = tmp->next;
	}
	printf("################\n");
}*/

void draw_area(t_env *e, int row_start, int col_start, t_int size, Uint32 color)
{
	int x;
	int y;

	y = row_start;
	x = col_start;
	while (y <= row_start + size.y)
	{
		x = (col_start);
		while (x <= (col_start + size.x))
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
	while (i < W_H)
	{
		put_pixel(e, ui_min, i, 0xffffff);
		i++;
	}
}
