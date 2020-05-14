/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:31:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 05:46:10 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_list_push_back(t_list *begin_list, void *content, size_t size)
{
	t_list *list;

	list = begin_list;
	if (list)
	{
		if (list->next)
			while (list->next)
				list = list->next;
		list->next = ft_lstnew(content, size);
		return(begin_list);
	}
	else
	{
		if (!(list = ft_lstnew(content, size)))
			ft_putstr("NO LIST\n");
		return (list);
	}
}