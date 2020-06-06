/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 23:20:56 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 03:46:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **link, t_list *new)
{
	if (link)
		new->next = *link;
	*link = new;
}

void	ft_list_inser(t_list *liste, void *content)
{
	t_list *new;
	t_list *tmp;

	new = malloc(sizeof(t_list));
	if (liste == NULL)
		return ;
	new->content = content;
	tmp = liste;
	new->next = tmp;
	liste = new;
}
