/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:31:36 by ahippoly          #+#    #+#             */
/*   Updated: 2020/05/04 19:50:38 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"
#include "../../includes/obj_parser.h"

t_list *assign_lst_value(char *line, int length)
{
	int i;
	float *values;
	int size;
	t_list *new;
	
	size = sizeof(float) * length;
	values = (float*)ft_memalloc(size);
	i = 0;
	line = skip_until_num(line);
	while (i < length)
	{
		line = ft_fatoi_ptr(line, &values[i++]);
		line = skip_until_space(line);
	}
	new = ft_lstnew(values, size);
	free(values);
	return (new);
}

static void		read_face_data(char *line, t_attr_lst *key_list, t_triangle new)
{
	int tmp_id;
	int i;
	int j;

	i = 0;
	line = skip_until_num(line);
	while (i < 3)
	{
		line = ft_atoi_ptr(line, &tmp_id);
		tmp_id--;
		if (tmp_id < key_list->v_size)
			assign_from_array(&new.p[i], 3, key_list->vert[tmp_id]);
		if (*line == '/')
		{
			line = ft_atoi_ptr(line + 1, &tmp_id);
			if (tmp_id < key_list->v_size)
				assign_from_array(&new.tx[i], 2, key_list->text[tmp_id]);
		}
		line = skip_until_space(line);
		i++;
	}
	new.tex = key_list->textured;
	key_list->tris[key_list->tris_curr_id++] = new;
}

static void		read_face_line(char *line, t_attr_lst *key_list, int mesh_id)
{
	t_triangle new;
	int tmp_id;
	int i;
	int j;

	if (ft_strnstr(line, "f ", 3))
	{
		if (key_list->tris_curr_id >= key_list->tris_size)
		{
			key_list->tris = (t_triangle*)double_array_size(key_list->tris, sizeof(t_triangle), key_list->tris_size);
			key_list->tris_size *= 2;
		}
		read_face_data(line, key_list, triangle_init(mesh_id));
	}
	free(line);
}

int read_line_key(char *line, t_attr_lst *key_list)
{
	if (ft_strnstr(line, "v ", 2))
	{
		ft_lstadd(&key_list->v, assign_lst_value(line, 3));
		key_list->v_size++;
	}
	if (ft_strnstr(line, "vt ", 3))
	{
		ft_lstadd(&key_list->vt, assign_lst_value(line, 2));
		key_list->textured = 1;
		key_list->vt_size++;
	}
	if (ft_strnstr(line, "vn ", 3))
	{
		ft_lstadd(&key_list->vn, assign_lst_value(line, 3));
		key_list->vn_size++;
	}
	free(line);
	return (0);
}

void free_tabs(t_attr_lst *key_list)
{
	int i;

	i = 0;
	while (i < key_list->v_size)
		free(key_list->vert[i++]);
	i = 0;
	while (i < key_list->vt_size)
		free(key_list->text[i++]);
	i = 0;
	while (i < key_list->vn_size)
		free(key_list->norm[i++]);
	free(key_list->vert);
	free(key_list->text);
	free(key_list->norm);
}

t_mesh	obj_parser(char *file, t_env *e)
{
	t_mesh obj;
	t_attr_lst key_list;
	char 	*line;
	int fd;
	int flag;

	fd = open(file, O_RDONLY);
	if (read(fd, &line, 0) == -1)
		ft_exit(e, "Invalid file input", 0);
	init_key_list(&key_list);
	flag = 1;
	while (get_next_line(fd, &line) > 0)
		if (read_line_key(line, &key_list) == 1)
			break;
	//free(line);
	create_triangle_list(&key_list);
	close(fd);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		read_face_line(line, &key_list, e->mesh_id);
	//free(line);
	free_tabs(&key_list);
	obj.tris = key_list.tris;
	obj.size = key_list.tris_curr_id;
	return (obj);
}