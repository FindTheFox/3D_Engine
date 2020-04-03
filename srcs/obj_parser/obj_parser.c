/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:31:36 by ahippoly          #+#    #+#             */
/*   Updated: 2020/04/03 23:38:26 by saneveu          ###   ########.fr       */
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

int read_face_line(char *line, t_attr_lst *key_list)
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
		new = triangle_init();
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
		key_list->tris[key_list->tris_curr_id++] = new;
	}
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
		key_list->vt_size++;
	}
	if (ft_strnstr(line, "vn ", 3))
	{
		ft_lstadd(&key_list->vn, assign_lst_value(line, 3));
		key_list->vn_size++;
	}
	return (0);
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
	create_triangle_list(&key_list);
	close(fd);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
		read_face_line(line, &key_list);
	free(line);
	obj.tris = key_list.tris;
	obj.size = key_list.tris_curr_id;
	return (obj);
}