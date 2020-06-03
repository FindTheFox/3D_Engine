/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:45:51 by brpinto           #+#    #+#             */
/*   Updated: 2020/06/03 16:50:37 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORGE_H
#define FORGE_H

# include "3d_engine.h"

typedef enum	e_l_choice
{
				WEAPON = 1,
				HUMANOID,
				ROOM,
				OUT
}				t_l_choice;

typedef struct	s_meshd
{
	char		*name;
	int			id;
}				t_meshd;

typedef struct	s_int
{
	int			x;
	int			y;
}				t_int;

typedef struct		s_bcontent
{
	int				elem_num;
	t_meshd			*meshd_tab;
}					t_bcontent;

typedef struct		s_button
{
	char			*title;
	int				x;
	int				y;
	int				w;
	int				h;
	int				cat;
	int				display;
	t_bcontent		content;
	struct s_button	*next;
}				t_button;

typedef struct	s_forge
{
	int			display;
	int			i;
	int			initialized;
	int			mesh_len;
	int			mesh_choice;
	int			over_y;
	int			button_hover;
	int			ui_start;
//	t_meshd		*meshd_tab;
	t_list		*selected;
	t_button	*buttons;
}				t_forge;

#endif
