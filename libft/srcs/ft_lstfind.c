/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 23:26:28 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/06 01:14:25 by saneveu          ###   ########.fr       */
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
    
    i = -1;
    tmp = *l;
    while (++i < index)
        tmp = tmp->next;
    return(tmp->content);

}