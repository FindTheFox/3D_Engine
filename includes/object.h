/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 22:31:20 by saneveu           #+#    #+#             */
/*   Updated: 2020/05/07 00:51:55 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "3d_engine.h"
# include "matrice.h"

typedef struct      s_vec
{
    float   x;
    float   y;
    float   z;
    float   w;
}                   t_vec;

typedef struct  s_hitbox
{
    t_vec       min;
    t_vec       max;
}               t_hitbox;


typedef struct      s_vec2d
{
    float   u;
    float   v;
    float   w;
}                   t_vec2d;

typedef struct      s_triangle
{
    t_vec           p[3];
    t_vec2d         tx[3];
    Uint8           tex;
    int             color;
    int             mesh_id;
    int             screen_pos;
    int             tri_id;
}                   t_triangle;

typedef struct      s_mesh
{
    t_triangle      *tris;
    int             size;
    float           ztheta;
    float           ytheta;
    float           xtheta;
    t_matrix        mattrans;
    t_vec           dir;
    int             color;
    SDL_Surface     *img;               //FREE ?
    char            *name;
    t_hitbox        hitbox;      
    int             id;
}                   t_mesh;

void            place_obj(t_mesh *obj, t_vec pos);

#endif