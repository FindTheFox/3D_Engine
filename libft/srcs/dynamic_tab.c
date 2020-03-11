/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:29:19 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/10 15:53:57 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		*dyaddress(t_dyntab *arr, int index)
{
	if (index > arr->cell_nb || index < 0)
		return (NULL);
	return ((void*)(arr->c + (index * arr->cell_size)));
}

void		free_dynarray(t_dyntab *arr)
{
	free(arr->c);
	ft_memset(arr, 0, sizeof(t_dyntab));
}

static int	start_size(int n)
{
	int		a;

	a = 2;
	while (n >= a)
		a *= 2;
	return (a);
}

void		clear_dynarray(t_dyntab *arr)
{
	arr->cell_nb = 0;
}

int			init_dynarray(t_dyntab *arr, int cell_size, int nb_cells)
{
	if (cell_size <= 0 || nb_cells < 0)
		return (-1);

	arr->cell_size = cell_size;
	arr->cell_nb = 0;
	arr->byte_size = start_size(cell_size * nb_cells + 1);
	if (arr->byte_size > 0 && (!(arr->c = malloc(arr->byte_size))
		|| !(arr->tmp = malloc(arr->byte_size))))
		return (-1);
	ft_memset(arr->c, 0, arr->byte_size);
	return (0);
}