/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:26:55 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/08 18:36:39 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

void            thread_init(t_env *e, t_thread *thread)
{
    thread->env = e;
    thread->tris = &e->to_raster;
    thread->i = 
    thread->start = 
}