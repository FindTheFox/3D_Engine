/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:05:00 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/02 21:08:27 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"


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


void	key_events(t_env *e)
{
	copy_keyboard_state(e->keyb_curr, e->keyb_prev);
	SDL_PumpEvents();
	e->keyb_curr = (Uint8 *)SDL_GetKeyboardState(NULL);
}
