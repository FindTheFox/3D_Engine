/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Creatf. 2020/05/02 21:05:00 by brpinto           #+#    #+#             */
/*   Updatf. 2020/05/12 08:40:15 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void type_choice(t_env *e)
{
	if(compare_keyb(e, SDL_SCANCODE_TAB))
	{
		if (e->l_choice < ROOM)
			e->l_choice++;
		else
			e->l_choice = 0;
	}
	if (compare_keyb(e, SDL_SCANCODE_RETURN))
		e->f.display = (e->l_choice == WEAPON) ? 1 : 0;
//	printf("%d\n", e->l_choice);
}

/*static void mesh_choice(t_env *e)
{
	int		j;
	int		max;
	t_meshd	meshd;
	int		k;

	j = 0;
	max = 0;
	k = 0;
	if (compare_keyb(e, SDL_SCANCODE_DOWN))
	{
		if (e->f.mesh_len <= 8)
		{
			if (e->f.mesh_choice < e->f.mesh_len - 1)
				e->f.mesh_choice++;
			else
				e->f.mesh_choice = 0;
		}
		else
		{
			if (e->f.mesh_choice == 7 && compare_keyb(e, SDL_SCANCODE_DOWN))
			{
				if (e->f.i < (e->f.mesh_len % 7))
					e->f.i++;
				j = e->f.i;
				max = (e->f.mesh_len % 7) - 1;
				while (j <= e->f.i + 7 && e->f.i <= max)
				{
					meshd.name = e->mesh[j].name;
					meshd.id = e->mesh[j].id;
					e->f.meshd_tab[k] = meshd;
					j++;
					k++;
				}
			}
			if (e->f.mesh_choice < 7)
				e->f.mesh_choice++;
		}
	}
	if (compare_keyb(e, SDL_SCANCODE_UP))
	{
		if (e->f.mesh_choice > 0)
			e->f.mesh_choice--;
		else
		{
			if (e->f.mesh_choice == 0)
			{
				if (e->f.i == 0)
				{
					if (e->f.mesh_len <= 8)
						e->f.mesh_choice = e->f.mesh_len - 1;
					else
						e->f.mesh_choice = 7;
				}
				else
				{
					e->f.i--;
					j = e->f.i;
					k = 0;
					while (j <= e->f.i + 7 && e->f.i >= 0)
					{
						meshd.name = e->mesh[j].name;
						meshd.id = e->mesh[j].id;
						e->f.meshd_tab[k] = meshd;
						j++;
						k++;
					}
				}
			}
		}
	}
	if (compare_keyb(e, SDL_SCANCODE_SPACE))
		save_mesh(e);
}*/


static void	copy_keyboard_state(Uint8 *keyb_curr, Uint8 keyb_prev[283])
{
	int i;

	i = 0;
	while (i < 284)
	{
		keyb_prev[i] = keyb_curr[i];
		i++;
	}
}

int	compare_keyb(t_env *e, int key)
{
	if (e->keyb_curr[key] && !e->keyb_prev[key])
		return (1);
	return (0);
}


void	forge_events(t_env *e)
{
	copy_keyboard_state(e->keyb_curr, e->keyb_prev);
	SDL_PumpEvents();
	e->keyb_curr = (Uint8 *)SDL_GetKeyboardState(NULL);
	type_choice(e);
//	mesh_choice(e);
}
