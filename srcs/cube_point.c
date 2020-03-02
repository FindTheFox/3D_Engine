/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:32:25 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:22:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"


void        init_cube(t_env *env)
{
    t_mesh mesh[1];
    t_triangle tri[12];

    env->nbmesh = 1;
    //env->mesh = (t_mesh *)malloc(sizeof(t_mesh));
    env->mesh = mesh;
    env->mesh[0].size = 12;
    env->mesh[0].tris = tri;
    //south
    env->mesh[0].tris[0].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[0].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[0].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};
    //printf("cube x = %f || cube y = %f || cube z = %f || cube w = %f\n", env->tris[0].p[2].x, env->tris[0].p[2].y, env->tris[0].p[2].z, env->tris[0].p[2].w);

    env->mesh[0].tris[1].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[1].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[1].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};

    //east
    env->mesh[0].tris[2].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[2].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[2].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[3].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[3].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[3].p[2] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};

    //NORTH
    env->mesh[0].tris[4].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[4].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[4].p[2] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[5].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[5].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[5].p[2] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};

    //west
    env->mesh[0].tris[6].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[6].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[6].p[2] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};

    env->mesh[0].tris[7].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[7].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[7].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};

    //top
    env->mesh[0].tris[8].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[8].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[8].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[9].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[9].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[9].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};    

    //bottom
    env->mesh[0].tris[10].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[10].p[1] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[10].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};

    env->mesh[0].tris[11].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[11].p[1] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[11].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};
}
/*
void        init_cube(t_env *env)
{
    //south
    env->tris[0].p[0] = (t_vec){0.0f, 0.0f, 0.0f};
    env->tris[0].p[1] = (t_vec){0.0f, 1.0f, 0.0f};
    env->tris[0].p[2] = (t_vec){1.0f, 1.0f, 0.0f};

    env->tris[1].p[0] = (t_vec){0.0f, 0.0f, 0.0f};
    env->tris[1].p[1] = (t_vec){1.0f, 1.0f, 0.0f};
    env->tris[1].p[2] = (t_vec){1.0f, 0.0f, 0.0f};

    //east
    env->tris[2].p[0] = (t_vec){1.0f, 0.0f, 0.0f};
    env->tris[2].p[1] = (t_vec){1.0f, 1.0f, 0.0f};
    env->tris[2].p[2] = (t_vec){1.0f, 1.0f, 1.0f};

    env->tris[3].p[0] = (t_vec){1.0f, 0.0f, 0.0f};
    env->tris[3].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
    env->tris[3].p[2] = (t_vec){1.0f, 0.0f, 1.0f};

    //NORTH
    env->tris[4].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
    env->tris[4].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
    env->tris[4].p[2] = (t_vec){0.0f, 1.0f, 1.0f};

    env->tris[5].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
    env->tris[5].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
    env->tris[5].p[2] = (t_vec){0.0f, 0.0f, 1.0f};

    //west
    env->tris[6].p[0] = (t_vec){0.0f, 0.0f, 1.0f};
    env->tris[6].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
    env->tris[6].p[2] = (t_vec){0.0f, 1.0f, 0.0f};

    env->tris[7].p[0] = (t_vec){0.0f, 0.0f, 1.0f};
    env->tris[7].p[1] = (t_vec){0.0f, 1.0f, 0.0f};
    env->tris[7].p[2] = (t_vec){0.0f, 0.0f, 0.0f};

    //top
    env->tris[8].p[0] = (t_vec){0.0f, 1.0f, 0.0f};
    env->tris[8].p[1] = (t_vec){0.0f, 1.0f, 1.0f};
    env->tris[8].p[2] = (t_vec){1.0f, 1.0f, 1.0f};

    env->tris[9].p[0] = (t_vec){0.0f, 1.0f, 0.0f};
    env->tris[9].p[1] = (t_vec){1.0f, 1.0f, 1.0f};
    env->tris[9].p[2] = (t_vec){1.0f, 1.0f, 0.0f};    

    //bottom
    env->tris[10].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
    env->tris[10].p[1] = (t_vec){0.0f, 0.0f, 1.0f};
    env->tris[10].p[2] = (t_vec){0.0f, 0.0f, 0.0f};

    env->tris[11].p[0] = (t_vec){1.0f, 0.0f, 1.0f};
    env->tris[11].p[1] = (t_vec){0.0f, 0.0f, 0.0f};
    env->tris[11].p[2] = (t_vec){1.0f, 0.0f, 0.0f};
}*/