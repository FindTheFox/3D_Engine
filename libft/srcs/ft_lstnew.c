/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 20:47:36 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 05:19:42 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
	{
		printf("NO NEW1\n");		
		return (NULL);
	}
	if (content)
	{
		if (!(new->content = malloc(content_size)))
		{
		printf("NO NEW2\n");

			return (NULL);
		}
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		printf("NO OBJ\n");
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	if (new == NULL)
		printf("NO NEW\n");
	return (new);
}
