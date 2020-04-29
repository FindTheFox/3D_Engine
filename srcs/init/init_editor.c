/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbenaroc <qbenaroc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 11:54:19 by qbenaroc          #+#    #+#             */
/*   Updated: 2020/04/29 14:08:37 by qbenaroc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void	init_editor(t_env *env)
{
	env->nbmesh = 1;
	if (!(env->mesh = (t_mesh *)malloc(sizeof(t_mesh) * env->nbmesh)))
		ft_exit(env, "Mesh Alloc Error", 0);
	env->mesh[0] = obj_parser("ressources/grid.obj", env);
	env->mesh[0].color = 0xffffff;
	env->mesh[0].name = "grid";
	env->mesh[0].dir = (t_vec){ 0, 0, 0, 0 };
	env->vlist.vcamera = (t_vec){0, 12.0f, -46.0f};
	printf("%s, nbmesh : %d", "init editor\n", env->nbmesh);
}
