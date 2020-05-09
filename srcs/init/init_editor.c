/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_editor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/09 23:19:15 by brpinto          ###   ########.fr       */
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
	t_meshd meshd;

	e->ed.test = 1;
	e->ed.mesh_len = 0;
	fd = open("./obj.doom2", O_RDONLY);
	get_next_line(fd, &line);
	close(fd);
	obj_list = ft_strsplit(line, ' ');
	while (obj_list[e->ed.mesh_len])
		e->ed.mesh_len++;
//	printf("%d\n", e->ed.mesh_len);
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->ed.mesh_len)))
		ft_exit(e, "Mesh Alloc Error", 0);
	i = 0;
	mi = 0;
	while (i < e->ed.mesh_len)
	{
		e->mesh_id = mi;
		e->mesh[mi] = obj_parser(obj_list[i], e);
		e->mesh[mi].color = colorset(e, mi);
		e->mesh[mi].name = obj_list[i];
		e->mesh[mi].id = mi;
//		printf("%s && %d\n", e->mesh[mi].name, e->mesh[mi].id);
		mi++;
		i++;
	}
	i = 0;
	if (!(e->ed.meshd_tab = (t_meshd *)malloc(sizeof(t_meshd) * e->ed.mesh_len - 1)))
		ft_exit(e, "Mesh info alloc error", 0);
	while(i < e->ed.mesh_len)
	{
		meshd.name = e->mesh[i].name;
		meshd.id = e->mesh[i].id;
		e->ed.meshd_tab[i] = meshd;
//		printf("%d\n", i);
		i++;
	}
//	e->ed.selected = ft_lstnew(NULL, 0);
}
