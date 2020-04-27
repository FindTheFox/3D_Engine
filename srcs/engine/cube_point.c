/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:32:25 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/28 00:52:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

void            init_cube(t_env *env)
{
    int i = 0;
    
    if (!(env->mesh = (t_mesh *)malloc(sizeof(t_mesh) * env->nbmesh)))
            ft_exit(env, "Mesh Alloc Error\n", 0);
    if (!(env->mesh[0].tris = (t_triangle *)ft_memalloc(sizeof(t_triangle)
            * 12)))
        ft_exit(env, "Malloc Mesh Error\n", 0);
    if (!(env->mesh[0].img = SDL_LoadBMP("ressources/img/wall.bmp")))
        ft_exit(env, "Load Bmp Failed\n", 0);
    
    env->mesh[0].size = 12;
    env->mesh[0].color = 0xfff0ff;
    //south
    env->mesh[0].tris[0].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[0].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[0].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};

    env->mesh[0].tris[0].tx[0] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[0].tx[1] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[0].tx[2] = (t_vec2d){1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[1].p[0] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[1].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[1].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};

    env->mesh[0].tris[1].tx[0] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[1].tx[1] = (t_vec2d){1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[1].tx[2] = (t_vec2d){1.0f, 0.0f, 1.0f};

    //east
    env->mesh[0].tris[2].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[2].p[1] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[2].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    
    env->mesh[0].tris[2].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[2].tx[1] = (t_vec2d){1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[2].tx[2] = (t_vec2d){1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[3].p[0] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[3].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[3].p[2] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};

    env->mesh[0].tris[3].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[3].tx[1] = (t_vec2d){1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[3].tx[2] = (t_vec2d){1.0f, 0.0f, 1.0f};

    //NORTH
    env->mesh[0].tris[4].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[4].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[4].p[2] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    
    env->mesh[0].tris[4].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[4].tx[1] = (t_vec2d){1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[4].tx[2] = (t_vec2d){0.0f, 1.0f, 1.0f};

    env->mesh[0].tris[5].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[5].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[5].p[2] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};

    env->mesh[0].tris[5].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[5].tx[1] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[5].tx[2] = (t_vec2d){0.0f, 0.0f, 1.0f};

    //west
    env->mesh[0].tris[6].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[6].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[6].p[2] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    
    env->mesh[0].tris[6].tx[0] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[6].tx[1] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[6].tx[2] = (t_vec2d){0.0f, 1.0f, 1.0f};

    env->mesh[0].tris[7].p[0] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[7].p[1] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[7].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};

    env->mesh[0].tris[7].tx[0] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[7].tx[1] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[7].tx[2] = (t_vec2d){0.0f, 0.0f, 1.0f};
    
    //top
    env->mesh[0].tris[8].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[8].p[1] = (t_vec){0.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[8].p[2] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    
    env->mesh[0].tris[8].tx[0] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[8].tx[1] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[8].tx[2] = (t_vec2d){1.0f, 1.0f, 1.0f};

    env->mesh[0].tris[9].p[0] = (t_vec){0.0f, 1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[9].p[1] = (t_vec){1.0f, 1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[9].p[2] = (t_vec){1.0f, 1.0f, 0.0f, 1.0f};

    env->mesh[0].tris[9].tx[0] = (t_vec2d){0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[9].tx[1] = (t_vec2d){1.0f, 1.0f, 1.0f};
    env->mesh[0].tris[9].tx[2] = (t_vec2d){1.0f, 1.0f, 1.0f};    

    //bottom
    env->mesh[0].tris[10].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[10].p[1] = (t_vec){0.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[10].p[2] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    
    env->mesh[0].tris[10].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[10].tx[1] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[10].tx[2] = (t_vec2d){0.0f, 0.0f, 1.0f};
    
    env->mesh[0].tris[11].p[0] = (t_vec){1.0f, 0.0f, 1.0f, 1.0f};
    env->mesh[0].tris[11].p[1] = (t_vec){0.0f, 0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[11].p[2] = (t_vec){1.0f, 0.0f, 0.0f, 1.0f};

    env->mesh[0].tris[11].tx[0] = (t_vec2d){1.0f, 0.0f, 1.0f};
    env->mesh[0].tris[11].tx[1] = (t_vec2d){0.0f, 0.0f, 1.0f};
    env->mesh[0].tris[11].tx[2] = (t_vec2d){1.0f, 0.0f, 1.0f};

    i = -1;
    while (++i < 12)
        env->mesh[0].tris[i].tex = 1;
}
