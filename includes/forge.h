/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:45:51 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/12 11:31:28 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORGE_H
#define FORGE_H

# include "3d_engine.h"

typedef enum	e_l_choice
{
				WEAPON = 0,
				TOOL,
				ROOM,
				OUT
}				t_l_choice;

typedef struct	s_meshd
{
	char		*name;
	int			id;
}				t_meshd;

typedef struct	s_forge
{
	int			display;
	int			i;
	int			initialized;
	int			mesh_len;
	int			mesh_choice;
	int			over_y;
	t_meshd		*meshd_tab;
	t_list		*selected;
}				t_forge;

#endif
