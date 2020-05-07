/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 04:21:54 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 05:12:34 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void        print_objlist(t_list *l)
{
    t_list  *tmp;

    tmp = l;
    if (!tmp)
        printf("PAS DE LIST\n");
    while (tmp)
    {
        printf("LIST ID: %d\n", tmp->index);
        tmp = tmp->next;
    }
}