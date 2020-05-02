/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:31:07 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/02 20:07:10 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void         key_tab(t_env *e)
{
    if (e->event.key.keysym.scancode == SDL_SCANCODE_W)
        e->key[W] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_S)
        e->key[S] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_A)
        e->key[A] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_D)
        e->key[D] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_Q)
        e->key[Q] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_E)
        e->key[E] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_R)
        e->key[R] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F)
        e->key[F] = e->event.type == SDL_KEYDOWN ? 1 : 0;

    else if (e->event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        e->key[SPACE] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_LCTRL)
        e->key[LCTRL] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_UP)
        e->key[UP] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_DOWN)
        e->key[DOWN] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_LEFT)
        e->key[LEFT] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            e->key[RIGHT] = e->event.type == SDL_KEYDOWN ? 1 : 0;

    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_0)
        e->key[NUM0] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_1)
        e->key[NUM1] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_2)
        e->key[NUM2] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_3)
        e->key[NUM3] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_4)
        e->key[NUM4] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_5)
        e->key[NUM5] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_6)
        e->key[NUM6] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_7)
        e->key[NUM7] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_8)
        e->key[NUM8] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_9)
        e->key[NUM9] = e->event.type == SDL_KEYDOWN ? 1 : 0;

    else if (e->event.type == SDL_MOUSEMOTION)
        e->key[MOUSE] = 1;
    else if (e->event.button.button == SDL_BUTTON_RIGHT)
        e->key[RCLICK] = e->event.type == SDL_MOUSEBUTTONDOWN ? 1 : 0;
    else if (e->event.button.button == SDL_BUTTON_LEFT)
        e->key[LCLICK] = e->event.type == SDL_MOUSEBUTTONDOWN ? 1 : 0;

    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_ENTER)
        e->key[PAD_ENTER] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
        e->key[PLUS] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
        e->key[MINUS] = e->event.type == SDL_KEYDOWN ? 1 : 0;

    else if (e->event.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
        e->key[SHIFT] = e->event.type == SDL_KEYDOWN ? 1 : 0;

    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F1)
        e->key[F1] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F2)
        e->key[F2] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F3)
        e->key[F3] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F4)
        e->key[F4] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F5)
        e->key[F5] = e->event.type == SDL_KEYDOWN ? 1 : 0;
        else if (e->event.key.keysym.scancode == SDL_SCANCODE_F6)
        e->key[F6] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F7)
        e->key[F7] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F8)
        e->key[F8] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F9)
        e->key[F9] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F10)
        e->key[F10] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F11)
        e->key[F11] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.scancode == SDL_SCANCODE_F12)
        e->key[F12] = e->event.type == SDL_KEYDOWN ? 1 : 0;

}

static void editor_events(t_env *e)
{
	if (e->event.key.keysym.scancode == SDL_SCANCODE_TAB && e->event.type == SDL_KEYDOWN)
		printf("l_choice = %d\n", e->l_choice);
}

void                event(t_env *env)
{
    while (SDL_PollEvent(&env->event))
    {
		if (env->state == FORGE)
		{
			editor_events(env);
		}
		else
		{
			if (env->event.key.keysym.scancode == SDLK_m
			&& env->event.type == SDL_KEYDOWN)
				printf("MENU\n");
            //menu(env->winsurf, 2);
		}
		if ((env->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && env->event.type == SDL_KEYDOWN) || env->event.type == SDL_QUIT)
				ft_exit(env, "fini\n", 1);
		key_tab(env);
    }
    camera_event(env);
    mesh_rot_event(env, env->usr.event_i_mesh);
    user_events(env);
    dev_event(env);
}
