/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/13 12:56:05 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static char **obj_file_parse(t_env *e)
{
	int fd;
	char **obj_list;
	char *line;

	fd = open("./obj.doom", O_RDONLY);
	get_next_line(fd, &line);
	close(fd);
	obj_list = ft_strsplit(line, ' ');
	while (obj_list[e->f.mesh_len])
		e->f.mesh_len++;
	return (obj_list);
}

static void	create_mesh_tab(t_env *e)
{
	int i;
	int mi;
	char **obj_list;
	
	obj_list = obj_file_parse(e);
	i = 0;
	mi = 0;
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->f.mesh_len)))
		ft_exit(e, "Mesh Alloc Error", 0);
	while (i < e->f.mesh_len)
	{
		e->mesh_id = mi;
		e->mesh[mi] = obj_parser(obj_list[i], e);
		e->mesh[mi].color = colorset(e, mi);
		e->mesh[mi].name = obj_list[i];
		e->mesh[mi].id = mi;
		mi++;
		i++;
	}
	// free obj_list
}

void init_forge(t_env *e)
{
	int i;
	t_meshd meshd;

	e->f.initialized = 1;
	e->f.mesh_len = 0;
	i = 0;
	create_mesh_tab(e);
	if (!(e->f.meshd_tab = (t_meshd *)malloc(sizeof(t_meshd) * e->f.mesh_len - 1)))
		ft_exit(e, "Mesh info alloc error", 0);
	while(i < e->f.mesh_len)
	{
		meshd.name = e->mesh[i].name;
		meshd.id = e->mesh[i].id;
		e->f.meshd_tab[i] = meshd;
		i++;
		// free meshd ?
	}
}
