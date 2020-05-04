/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 01:43:54 by user42            #+#    #+#             */
/*   Updated: 2020/05/02 01:51:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3d_engine.h"


static void     mat_engine_set(t_env *e)
{
    int i;

    i = 0;
    while (i < 4)
    {
        e->mlist.camrotx.m[i][i] = 1.0f;
        e->mlist.camroty.m[i][i] = 1.0f;
        e->mlist.matworld.m[i][i] = 1.0f;
        e->mlist.matview.m[i][i] = 1.0f;
        e->mlist.mattranslate.m[i][i] = 1.0f;
        e->mlist.matrotx.m[i][i] = 1.0f;
        e->mlist.matroty.m[i][i] = 1.0f;
        e->mlist.matrotz.m[i][i] = 1.0f;
        e->mlist.matproj.m[i][i] = 1.0f;
        i++;
    }
}

static void     mat_engine(t_env *e)
{
    int i;
    int j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
        {
            ft_memset(&e->mlist.camrotx.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.camroty.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matworld.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matview.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.mattranslate.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matrotx.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matroty.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matrotz.m[i][j], 0, sizeof(float) * 4);
            ft_memset(&e->mlist.matproj.m[i][j], 0, sizeof(float) * 4);
        }
    }
    mat_engine_set(e);
}

static void     mat_mesh(t_env *e)
{
    int index;
    int i;
    int j;

    index = -1;
    while (++index < e->nbmesh)
    {
        i = -1;
        while (++i < 4)
        {
            j = -1;
            while (++j < 4)
                e->mesh[index].mattrans.m[i][j] = 0;
        }
    }
}

void     set_matrice(t_env *e)
{
    mat_engine(e);
    mat_mesh(e);
}
