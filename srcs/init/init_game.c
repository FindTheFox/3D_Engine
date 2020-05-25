/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbenaroc <qbenaroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 18:40:11 by qbenaroc          #+#    #+#             */
/*   Updated: 2020/05/25 17:12:26 by qbenaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void		init_game(t_env *e)
{
	t_mesh		new;

	new = obj_parser("ressources/wooden_crate.obj", e);

	e->vlist.vcamera = (t_vec){0, 0, 0, 0};
	printf("cube init\n");
	e->nbmesh = 1;
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->nbmesh)))
		ft_exit(e, "Mesh Alloc Error", 0); 
	e->mesh[0] = obj_parser("ressources/wooden_crate.obj", e);
	if (!(e->mesh[0].img = SDL_LoadBMP("ressources/wood_crate_10cm.bmp")))
		ft_exit(e, "DooM: Load Bmp Failed\n", 0);
	e->mesh[0].dir = (t_vec){0.0f, 0.0f, 10.0f, 0.0f};
}
