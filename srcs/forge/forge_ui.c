/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/12 11:38:20 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void __attribute((destructor)) checkleaks();

void checkleaks()
{
	printf("Après l'exit ?\n");
	while (1)
		;
}

void forge_run(t_env *e)
{
	if (!e->f.initialized)
		init_forge(e);
	draw_v(e);
	draw_list_component(e);
}
