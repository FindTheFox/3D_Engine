/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_tab2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:33:30 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/05 22:22:12 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		realloc_content(t_dyntab *arr)
{
	void	*tmp;
	int		prev_size;

	prev_size = arr->byte_size;
	arr->byte_size *= 2;
	if (!(tmp = malloc(arr->byte_size))
		|| !(arr->tmp = malloc(arr->byte_size)))
		return (-1);
	ft_memcpy(tmp, arr->c, prev_size);
	free(arr->c);
	arr->c = tmp;
	return (0);
}

int		pop_dyntab(t_dyntab *arr, bool front)
{
	int		len;

	len = (arr->cell_nb - 1) * arr->cell_size;
	if (front)
	{
		ft_memcpy(arr->tmp, (void*)(arr->c + arr->cell_size), len);
		ft_memcpy(arr->c, arr->tmp, len);
	}
	arr->cell_nb--;
	return (0);
}

int		remove_dyntab(t_dyntab *arr, int index)
{
	if (index > arr->cell_nb || index < 0)
		return (-1);
	free((void*)(arr->c + (index * arr->cell_size)));
	arr->cell_nb--;
	return(0);
}

int		push_dyntab(t_dyntab *arr, void *src, bool front)
{
	int		len;

	len = arr->cell_nb * arr->cell_size;
	if ((++arr->cell_nb) * arr->cell_size >= arr->byte_size)
		while (arr->cell_nb * arr->cell_size >= arr->byte_size)
			if (realloc_content(arr))
				return (-1);
	if (front)
	{
		ft_memcpy(arr->tmp, arr->c, len);
		ft_memcpy(arr->c, src, arr->cell_size);
		ft_memcpy((void*)(arr->c + arr->cell_size), arr->tmp, len);
	}
	else
		ft_memcpy((void*)(arr->c + len), src, arr->cell_size);
	return (0);
}