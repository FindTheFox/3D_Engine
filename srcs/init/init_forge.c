/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/12 09:23:54 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void init_forge(t_env *e)
{
	int fd;
	char *line;
	char **obj_list;
	int i;
	int mi;
	t_meshd meshd;

	e->f.test = 1;
	e->f.mesh_len = 0;
	fd = open("./obj.doom", O_RDONLY);
	get_next_line(fd, &line);
	close(fd);
	obj_list = ft_strsplit(line, ' ');
	while (obj_list[e->f.mesh_len])
		e->f.mesh_len++;
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->f.mesh_len)))
		ft_exit(e, "Mesh Alloc Error", 0);
	i = 0;
	mi = 0;
	while (i < e->f.mesh_len)
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
	if (!(e->f.meshd_tab = (t_meshd *)malloc(sizeof(t_meshd) * e->f.mesh_len - 1)))
		ft_exit(e, "Mesh info alloc error", 0);
	while(i < e->f.mesh_len)
	{
		meshd.name = e->mesh[i].name;
		meshd.id = e->mesh[i].id;
		e->f.meshd_tab[i] = meshd;
//		printf("%d\n", i);
		i++;
	}
//	e->f.selected = ft_lstnew(NULL, 0);
}
