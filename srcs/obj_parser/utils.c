/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 22:52:21 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/03 23:41:10 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj_parser.h"

void free_lst(t_list *lst)
{
	t_list *tmp;

	if (lst == NULL)
		printf("List already done\n");
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (lst == NULL)
			printf("List ended\n");
		free(tmp);
	}
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
		if (lst == NULL)
			printf("Lst ended, size = %i\n", size);
		free(tmp->content);
		free(tmp);
	}
	if (lst == NULL)
		printf("Lst ended2\n");
	free_lst(lst);
	return (array_lst);
}

void create_triangle_list(t_attr_lst *key_list)
{
	key_list->vert = create_array_from_list(key_list->v, key_list->v_size, 3);
	key_list->text = create_array_from_list(key_list->vt, key_list->vt_size, 2);
	key_list->norm = create_array_from_list(key_list->vn, key_list->vn_size, 3);
}

char *skip_until_num(char *str)
{
	while (*str != 0 && (*str < '0' || *str > '9') && *str != '-')
		str++;
	return (str);
}

char *skip_until_space(char *str)
{
	while (*str != 0 && *str != ' ')
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