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

void read_line_key(char *line, t_attr_lst *key_list)
{
	if (ft_strstr(line, "v "))
	{
		ft_lstadd(&key_list->v, assign_lst_value(line, 3));
		key_list->v_size++;
		// printf("line = %s\n", line);
	}
}

double **create_array_from_list(t_list *lst, int size, int content_length)
{
	double **array_lst;
	double *content;
	t_list *tmp;
	int i;

	i = 0;
	array_lst = (double**)malloc(size * sizeof(double*));
	while (size > 0)
	{
		array_lst[--size] = (double*)malloc(sizeof(double) * content_length);
		i = 0;
		content = (double*)lst->content;
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
	double **vert;
	double **text;
	double **norm;

	vert = create_array_from_list(key_list->v, key_list->v_size, 3);
	text = create_array_from_list(key_list->vt, key_list->vt_size, 2);
	norm = create_array_from_list(key_list->vn, key_list->vn_size, 3);

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
		read_line_key(line, &key_list);
	}
	print_t_list(key_list.v);
	create_triangle_list(&key_list);


	obj.size = 0;
	return (obj);
}