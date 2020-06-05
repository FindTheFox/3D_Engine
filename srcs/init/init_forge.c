/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:23:41 by brpinto           #+#    #+#             */
/*   Updated: 2020/06/05 11:23:47 by brpinto          ###   ########.fr       */
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
//		e->mesh[mi].id = ft_atoi(e->mesh[mi].name);
		mi++;
		i++;
	}
}

void get_content(t_env *e, t_button *button)
{
	int i;
	int j;
	t_meshd meshd;
	char str[2];

	i = 0;
	j = 0;
/*	while (tmp)
	{
		if (tmp->cat == cat)
			break;
		tmp = tmp->next;
	}*/
	while (e->mesh[i].name && i < e->f.mesh_len)
	{
//		printf("%c && %d\n", e->mesh[i].name[0], button->cat);
		str[0] = (e->mesh[i].name)[0];
		str[1] = '\0';
		if (ft_atoi(str) == button->cat)
			button->content.elem_num++;
		i++;
	}
	if (button->content.elem_num > 8)
		button->content.maxh = 8;
	else
		button->content.maxh = button->content.elem_num;
//	printf("%d\n", tmp->content.elem_num);
	i = 0;
	if (!(button->content.meshd_tab = (t_meshd *)malloc(sizeof(t_meshd) * button->content.elem_num - 1)))
		ft_exit(e, "Mesh info alloc error", 0);
	while(i < e->f.mesh_len && j < button->content.elem_num)
	{
		str[0] = (e->mesh[i].name)[0];
		str[1] = '\0';
		if (ft_atoi(str) == button->cat)
		{
			meshd.name = e->mesh[i].name;
			meshd.id = j;
			button->content.meshd_tab[j] = meshd;
			j++;
		}
		i++;
		// free meshd ?
	}
}

void init_forge(t_env *e)
{
	e->f.initialized = 1;
	create_mesh_tab(e);
	button_init(e, (W_W - (W_W / 3) + 40), 40, 1, "Weapon");
	button_init(e, (W_W - (W_W / 3) + 40), 80, 2, "Humanoid");
}
