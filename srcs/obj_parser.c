/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahippoly <ahippoly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:31:36 by ahippoly          #+#    #+#             */
/*   Updated: 2020/03/10 05:10:45 by ahippoly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"
#include "../includes/obj_parser.h"

void print_t_list(t_list *list)
{
	double *content;
	while (list)
	{
		content = (double*)list->content;
		printf("content of list = %f", *(content));
		printf(" %f", *(content + 1));
		printf(" %f\n", *(content + 2));
		list = list->next;
	}
}

char *skip_until_num(char *str)
{
	while (*str != 0 && (*str < '0' || *str > '9') && *str != '-')
		str++;
	return (str);
}

char *skip_until_space(char *str)
{
	while (*str != 0 *str != ' ')
		str++;
	return (str);
}

void	*double_array_size(void *data, int unit_size, size_t array_length)
{
	void	*new_data;
	size_t	array_size;

	array_size = unit_size * array_length;
	if (!(new_data = malloc(array_size * 2)))
		return (NULL);
	ft_memcpy(new_data, data, array_size);
	free(data);
	return (new_data);
}

char	*ft_fatoi_ptr(char *str, double *value)
{
	double	nb;
	double	pow;
	int		neg;

	nb = 0;
	neg = 1;
	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		str++ && (neg = -1);
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*(str++) - '0');
	if (*str == '.')
	{
		str++;
		pow = 0.1;
		while (*str >= '0' && *str <= '9')
		{
			nb += (*(str++) - '0') * pow;
			pow /= 10;
		}
	}
	printf("nb = %f\n", nb);
	*value = nb * neg;
	return (str);
}

t_list *assign_lst_value(char *line, int length)
{
	int i;
	double *values;
	int size;
	t_list *new;
	
	size = sizeof(double) * length;
	values = (double*)ft_memalloc(size);
	i = 0;
	line = skip_until_num(line);
	while (i < length)
		line = ft_fatoi_ptr(line, &values[i++]);
	printf("value = %f\n", values[0]);
	printf("line = %s\n", line);

	new = ft_lstnew(values, size);
	free(values);
	return (new);
}

t_triangle triangle_init(void)
{
	t_triangle	new;
	t_vec		vec;
	t_tex		tex;
	int			i;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	vec.w = 1;
	tex.u = 0;
	tex.v = 0;
	i = 0;
	while (i < 3)
	{
		new.p[i] = vec;
		new.t[i] = tex;
		i++;
	}
	return (new);
}

void assign_from_array(void *data, int length, float *values)
{
	float *to_assign;
	int i;

	to_assign = (float*)data;
	i = 0;
	while (i < length)
		to_assign[i] = values[i];
}

void read_face_line(char *line, t_attr_lst *key_list)
{
	t_triangle new;
	int tmp_id;
	int text_id;
	int i;
	int j;

	if (ft_strnstr(line, "f ", 2))
	{
		if (key_list->tris_curr_id >= key_list->tris_size)
		{
			key_list->tris = (t_triangle*)double_array_size(key_list->tris, sizeof(t_triangle), key_list->tris_size);
			key_list->tris_size *= 2;
		}
		// printf("line = %s\n", line);
		new = triangle_init();
		i = 0;
		line = skip_until_num(line);
		while (i < 3)
		{
			line = ft_fatoi_ptr(line, tmp_id);
			if (vert_id < key_list->v_size)
				assign_from_array(new.p, 3, key_list->vert[tmp_id]);
			if (*line == '/')
			{
				line = ft_fatoi_ptr(line + 1, tmp_id);
				if (vert_id < key_list->v_size)
					assign_from_array(new.t, 2, key_list->text[tmp_id]);
			}
			line = skip_until_space(line);
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
		// printf("line = %s\n", line);
	}
	if (ft_strnstr(line, "vt ", 3))
	{
		ft_lstadd(&key_list->vt, assign_lst_value(line, 2));
		key_list->vt_size++;
		// printf("line = %s\n", line);
	}
	if (ft_strnstr(line, "vn ", 3))
	{
		ft_lstadd(&key_list->vn, assign_lst_value(line, 3));
		key_list->vn_size++;
		// printf("line = %s\n", line);
	}
	if (ft_strnstr(line, "f ", 2))
		return (1);
	return (0);
}

float **create_array_from_list(t_list *lst, int size, int content_length)
{
	float **array_lst;
	float *content;
	t_list *tmp;
	int i;

	i = 0;
	array_lst = (float**)malloc(size * sizeof(float*));
	while (size > 0)
	{
		array_lst[--size] = (float*)malloc(sizeof(float) * content_length);
		i = 0;
		content = (float*)lst->content;
		while (i < content_length)
		{
			array_lst[size][i] = content[i];
			i++;
		}
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	return (array_lst);
}

void init_key_list(t_attr_lst *key_list)
{
	key_list->v = NULL;
	key_list->vt = NULL;
	key_list->vn = NULL;
	key_list->v_size = 0;
	key_list->vt_size = 0;
	key_list->vn_size = 0;
	key_list->tris_size = FACES_ARRAY_SIZE;
	key_list->tris = (t_triangle*)malloc(sizeof(t_triangle) * FACES_ARRAY_SIZE);
}


void print_array(double **array, int size, int content_size, char *name)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		printf("%s = ", name);
		while (j < content_size)
			printf("%f ", array[i][j++]);
		i++;
		printf("\n");
	}
	
}

void create_triangle_list(t_attr_lst *key_list)
{
	float **vert;
	float **text;
	float **norm;

	key_list->vert = create_array_from_list(key_list->v, key_list->v_size, 3);
	key_list->text = create_array_from_list(key_list->vt, key_list->vt_size, 2);
	key_list->norm = create_array_from_list(key_list->vn, key_list->vn_size, 3);

	print_array(vert, key_list->v_size, 3, "vertices");
}

t_mesh	obj_parser(char *file, t_env *e)
{
	t_mesh obj;
	t_attr_lst key_list;
	char 	*line;
	int fd;
	
	fd = open(file, O_RDONLY);
	if (read(fd, &line, 0) == -1)
		ft_exit(e, "Invalid file input", 0);
	init_key_list(&key_list);
	while (get_next_line(fd, &line) > 0)
	{
		if (read_line_key(line, &key_list) == 1)
			break;
	}
	create_triangle_list(&key_list);
	while (get_next_line(fd, &line) > 0)
	{
		read_line_key(line, &key_list);
	}
	print_t_list(key_list.v);


	obj.size = 0;
	return (obj);
}