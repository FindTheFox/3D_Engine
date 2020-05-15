/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/15 10:21:01 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

/*
void __attribute((destructor)) checkleaks();

void checkleaks()
{
	printf("Après l'exit ?\n");
	while (1)
		;
}
*/

static void display_ui(t_env *e)
{
	t_int start;
	t_int size;

	start.x = (W_W - (W_W / 3)) + 40;
	start.y = 40;
	size.y = 30;
	size.x = (W_W - (W_W / 3)) / 3;
	draw_v(e);
	draw_list_component(e, start, size, 8, "Titre 1");
	start.y = 80;
	draw_list_component(e, start, size, 8, "Titre 2");
}

void forge_run(t_env *e)
{
	if (!e->f.initialized)
		init_forge(e);
	display_ui(e);
}
