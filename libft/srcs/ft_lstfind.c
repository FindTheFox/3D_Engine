/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:26:28 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 04:47:18 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
** Attention l'index doit etre en base 10 pour inclure le 0
*/

void        *ft_listfind(t_list **l, int index)
{
    t_list  *tmp;
    int     i;

    tmp = *l;
    i = -1;
    while (++i < index && tmp->next)
        tmp = tmp->next;
    return (tmp->content);
}

t_list      *ft_listindex(t_list *l)
{
    t_list *tmp;
    int    i;
    
    if (l == NULL)
        return (l);
    tmp = l;
    i = 0;
    while (tmp != NULL)
    {
        tmp->index = i;
        tmp = tmp->next;
        i++;
    }
    return (l);
}