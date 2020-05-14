/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 23:00:03 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 02:36:11 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	(*del)((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

t_list		*ft_lstremove(t_list *alst, int index)
{
	t_list	*tmp;
	t_list	*previous;

	if (alst == NULL)
		return (alst);
	previous = alst;
	if (previous->index == index)
	{
		alst = previous->next;
		free(previous);
		return (alst);
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (tmp->index == index)
		{	
			previous->next = tmp->next;
			free(tmp);
			return(alst);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	return (alst);
}