/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_stuff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 23:14:03 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/03 23:41:14 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj_parser.h"

void print_array(float **array, int size, int content_size, char *name)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		printf("%s =  ", name);
		while (j < content_size)
			printf("%f ", array[i][j++]);
		i++;
		printf("\n");
	}
	
}

void print_faces_content(t_triangle *tris, int size)
{
	int i;
	int j;
	i = 0;
	while (i < size)
	{
		printf("   triangle num %i\n", i);
		j = 0;
		while (j < 3)
		{
			printf("x = %f, y = %f, z = %f; u = %f v = %f\n", tris[i].p[j].x, tris[i].p[j].y, tris[i].p[j].z, tris[i].tx[j].u, tris[i].tx[j].v);
			j++;
		}
		
		i++;
	}
}

void print_t_list(t_list *list)
{
	float *content;
	while (list)
	{
		content = (float*)list->content;
		printf("content of list = %f", *(content));
		printf(" %f", *(content + 1));
		printf(" %f\n", *(content + 2));
		list = list->next;
	}
}
