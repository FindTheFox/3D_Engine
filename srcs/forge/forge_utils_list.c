/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_utils_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 16:05:35 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/25 12:42:08 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

/*static t_button         *button_new(t_button button)
{
	t_button  *new;

	if (!(new = malloc(sizeof(t_button))))
		return (NULL);
	if (content)
	{
		if (!(new->content = malloc(content_size)))
			return (NULL);
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}*/

/*void add_button(t_env *e, t_button button)
{
	t_button *tmp;

	tmp = e->f.buttons;
	while (tmp)
	{
		if ((int)tmp->cat == button.cat)
			return ;
		tmp = tmp->next;
	}
//	tmp = ft_lstnew("\0", e->f.meshd_tab[e->f.mesh_choice].id);
	ft_lstadd(&e->f.selected, tmp);
	tmp = e->f.selected;
	while (tmp)
	{
		printf("%d\n", (int)tmp->content_size);
		tmp = tmp->next;
	}
	printf("################\n");
}*/

void save_mesh(t_env *e)
{
	t_list *tmp;

	tmp = e->f.selected;
	while (tmp)
	{
		if ((int)tmp->content_size == e->f.meshd_tab[e->f.mesh_choice].id)
			return ;
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", e->f.meshd_tab[e->f.mesh_choice].id);
	ft_lstadd(&e->f.selected, tmp);
	tmp = e->f.selected;
	/*	while (tmp)
		{
		printf("%d\n", (int)tmp->content_size);
		tmp = tmp->next;
		}
		printf("################\n");*/
}
