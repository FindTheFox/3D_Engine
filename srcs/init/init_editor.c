/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/04 19:05:06 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void init_editor(t_env *env)
{
	env->nbmesh = 1;
/*	if (!(env->mesh = (t_mesh *)malloc(sizeof(t_mesh) * env->nbmesh)))
		ft_exit(env, "Mesh Alloc Error", 0);
	env->mesh[0] = obj_parser("wood_box_10cm.obj",env);
	env->mesh[0].color = 0xffffff;
	env->mesh[0].name = "wood_box_10cm.obj";
	env->mesh[0].dir = (t_vec){0, 0, 0, 0};
	env->vlist.vcamera = (t_vec){0.0f, 12.0f, -45.0f};
*/
}
