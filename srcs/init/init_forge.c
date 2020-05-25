/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/25 19:57:18 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

/*static char *get_obj_name(char *path)
{
	char	*name;
	int		len;

	len = 0;
	while (path[len])
		len++;
	name = ft_strsub(path, 11, len - 11);
	return (name);
}*/

static char **list_to_tab(t_env *e, t_list **list)
{
	char	**tab;
	int		len;
	t_list	*tmp;
	int		i;

	len = 0;
	i = 0;
	tmp = *list;
	if ((tab = malloc(sizeof(char *) * e->f.mesh_len)) == NULL)
		return (NULL);
	while (tmp)
	{
		tab[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

static t_list *file_parse(t_list **list)
{
	int		fd;
	int		ret;
	t_list	*new;
	char	*line;

	if((fd = open("./obj.doom", O_RDONLY)) < 0)
		return (NULL);
	if ((ret = get_next_line(fd, &line)) < 0)
		return (NULL);
	*list = ft_lstnew(line, ft_strlen(line) + 1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		new = ft_lstnew(line, ft_strlen(line) + 1);
		free(line);
		ft_lstadd(list, new);
	}
	close(fd);
	return (*list);
}

static void	create_mesh_tab(t_env *e)
{
	int i;
	int mi;
	char **objs;
	t_list	*obj_list;
	t_list *tmp;

	obj_list = file_parse(&obj_list);
	tmp = obj_list;
	while (tmp)
	{
		e->f.mesh_len++;
		tmp = tmp->next;
	}
	objs = list_to_tab(e, &obj_list);
	i = 0;
	mi = 0;
	if (!(e->mesh = (t_mesh *)malloc(sizeof(t_mesh) * e->f.mesh_len)))
		ft_exit(e, "Mesh Alloc Error", 0);
	while (i < e->f.mesh_len)
	{
		e->mesh_id = mi;
		e->mesh[mi] = obj_parser(objs[i], e);
		e->mesh[mi].color = colorset(e, mi);
		e->mesh[mi].name = ft_strsub(objs[i], 11, ft_strlen(objs[i]) - 11);
		e->mesh[mi].id = ft_atoi(e->mesh[mi].name);
		mi++;
		i++;
	}
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
	button_init(e, (W_W - (W_W / 3) + 40), 40, 0, 3);
	button_init(e, (W_W - (W_W / 3) + 40), 80, 1, 3);
}
