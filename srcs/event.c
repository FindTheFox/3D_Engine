/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:31:07 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/20 18:20:46 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static void         move_events(t_env *e)
{
    if (e->event.key.keysym.sym == SDLK_w)
        e->key[W] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_s)
        e->key[S] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_a)
        e->key[A] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_d)
        e->key[D] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_q)
        e->key[Q] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_e)
        e->key[E] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_r)
        e->key[R] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_f)
        e->key[F] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_UP)
        e->key[UP] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_DOWN)
        e->key[DOWN] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_8)
        e->key[NUM8] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_2)
        e->key[NUM2] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_4)
        e->key[NUM4] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_6)
        e->key[NUM6] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_1)
        e->key[NUM1] = e->event.type == SDL_KEYDOWN ? 1 : 0;
    else if (e->event.key.keysym.sym == SDLK_KP_3)
        e->key[NUM3] = e->event.type == SDL_KEYDOWN ? 1 : 0;
}

static void         camera_move_event(t_env *e)
{
    if (e->key[UP] || e->key[DOWN])
    {
        e->vlist.forward = vectormult(e->vlist.lookdir, 8.0 * e->theta);
        if (e->key[UP])
            e->vlist.vcamera = vectoradd(e->vlist.vcamera, e->vlist.forward);
        else if (e->key[DOWN])
            e->vlist.vcamera = vectorsub(e->vlist.vcamera, e->vlist.forward);
    }
    if (e->key[W])
        e->vlist.vcamera.y += 8.0 * e->theta;
    if (e->key[S])
        e->vlist.vcamera.y -= 8.0 * e->theta;
    if (e->key[A])
        e->vlist.vcamera.x += 8.0 * e->theta;
    if (e->key[D])
        e->vlist.vcamera.x -= 8.0 * e->theta;
}

void                camera_rot_event(t_env *e)
{
    if (e->key[Q])
    {
        e->yaw -= 2.0 * e->theta;
        init_matrix_roty(&e->mlist.camroty, e->yaw);
    }
    if (e->key[E])
    {
        e->yaw += 2.0 * e->theta;
        init_matrix_roty(&e->mlist.camroty, e->yaw);    
    }
    if (e->key[R])
    {
        e->xaw -= 2.0 * e->theta;
        init_matrix_rotx(&e->mlist.camrotx, e->xaw);
    }
    if (e->key[F])
    {
        e->xaw += 2.0 * e->theta;
        init_matrix_rotx(&e->mlist.camrotx, e->xaw);    
    }
}

void                mesh_rot_event(t_env *e)
{
    if (e->key[NUM8])
        e->xtheta += 2.0 * e->theta;
    if (e->key[NUM2])
        e->xtheta -= 2.0 * e->theta;
    if (e->key[NUM4])
        e->ytheta -= 2.0 * e->theta;
    if (e->key[NUM6])
        e->ytheta += 2.0 * e->theta;
    if (e->key[NUM1])
        e->ztheta -= 2.0 * e->theta;
    if (e->key[NUM3])
        e->ztheta += 2.0 * e->theta;
}

void                event(t_env *env)
{
    while (SDL_PollEvent(&env->event))
    {
        if ((env->event.key.keysym.sym == SDLK_ESCAPE
		&& env->event.type == SDL_KEYDOWN)
		|| env->event.type == SDL_QUIT)
            ft_exit(env, "fini\n", 1);
        move_events(env);
    }
    camera_move_event(env);
    camera_rot_event(env);
    mesh_rot_event(env);
}
