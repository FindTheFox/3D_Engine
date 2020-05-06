/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/06 19:48:45 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void init_editor(t_env *e)
{
	int fd;
	char *line;
	char **obj_list;
	int i;
	int mi;
	
	e->ed.test = 1;
	e->ed.mesh_len = 0;
	fd = open("./obj.doom", O_RDONLY);
	get_next_line(fd, &line);
	close(fd);
	obj_list = ft_strsplit(line, ' ');
	while (obj_list[e->ed.mesh_len])
		e->ed.mesh_len++;
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->ed.mesh_len)))
		ft_exit(e, "Mesh Alloc Error", 0);
	i = 1;
	mi = 0;
	while (i < e->ed.mesh_len)
	{
		e->mesh_id = mi;
		e->mesh[mi] = obj_parser(obj_list[i], e);
		e->mesh[mi].color = colorset(e, mi);
		e->mesh[mi].name = obj_list[i];
		e->mesh[mi].id = mi;
		mi++;
		i++;
	}
}
