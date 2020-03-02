/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_engine.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:57:46 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:21:06 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../SDL/SDL.h"
# include "../libft/includes/libft.h"
# include <fcntl.h>
 
# define W_W 800
# define W_H 800

# define KEY_NB 16
# define W 0
# define A 1
# define S 2
# define D 3
# define E 4
# define Q 5
# define UP 6
# define DOWN 7
# define R 8
# define F 9
# define NUM8 10
# define NUM2 11
# define NUM4 12
# define NUM6 13
# define NUM1 14
# define NUM3 15

typedef struct      s_line
{
    int             coef;
    int             i;
}                   t_line;

typedef struct      s_rgba
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
}                   t_rgba;

typedef struct      s_vec
{
    float   x;
    float   y;
    float   z;
    float   w;
}                   t_vec;

typedef struct      s_triangle
{
    t_vec   p[3];
    int     color;
}                   t_triangle;

typedef struct      s_mesh
{
    t_triangle      *tris;
    int             size;
}                   t_mesh;

typedef struct      s_matrix
{
    float           m[4][4];
}                   t_matrix;

typedef struct      s_fill 
{
    int           yend;
    int           xend;
    int           ystart;
    int           xstart;
    float         m0;
    float         m1;
    float         x1;
    float         x0;
}                   t_fill;

typedef struct      s_vlist
{
    t_vec           vcamera;
    t_vec           light_dir;
    t_vec           voff_set;
    t_vec           up;
    t_vec           lookdir;
    t_vec           target;
    t_vec           right;
    t_vec           forward;
}                   t_vlist;

typedef struct      s_mlist
{
    t_matrix        matproj;
    t_matrix        matrotz;
    t_matrix        matrotx;
    t_matrix        matroty;
    t_matrix        mattranslate;
    t_matrix        matview;
    t_matrix        matworld;
    t_matrix        camroty;
    t_matrix        camrotx;
}                   t_mlist;

typedef struct      s_parser
{
    char            *str;
    int             vi;
    int             ti;
    t_triangle      *tri;
    t_vec           *vertex;
    int             vnb;
    int             fnb;
    int             mi;
}                   t_parser;

typedef struct      s_env
{
    float           ytheta;
    float           xtheta;
    float           ztheta;
    float           theta;
    float           zoom;
    float           fNear;
    float           fFar;
    float           fFov;
    float           fAspectRatio;
    float           fFovRad;
    float           fps;
    float           time;
    float           frametime;
    float           yaw;
    float           xaw;
    int             key[KEY_NB];
    t_vlist         vlist;
    t_mlist         mlist;
    t_fill          fill;
    t_triangle      tris[12];
    //t_triangle      *buffer;
    t_triangle      tritransform;
    t_triangle      triprojected;
    t_mesh          *mesh;
    int             nbmesh;
    t_parser        parse;
    t_rgba          rgba;
    t_line          line;
    SDL_Window      *window;
    SDL_Event       event;
    SDL_Renderer    *rend;
    SDL_Texture     *screen;
    SDL_Surface     *winsurf;
}                   t_env;

/*
**Global
*/

void        file_parser(t_env *e, char *file, int mi);
void        engine_3d(t_env *env);
void        ft_exit(t_env *env, char *s, int flag);
void        init_cube(t_env *env);
void        init_sdl(t_env *env);
void        init_data(t_env *e);
void        sdl_render(t_env *e);
void        draw_line(t_env *e, t_vec v1, t_vec v2, int color);
/*
**Matrice calcul and init
*/

void        init_matrix_proj(t_env *e);
void        init_matrix_rotx(t_matrix *m, float theta);
void        init_matrix_rotz(t_matrix *m, float theta);
void        init_matrix_roty(t_matrix *m, float theta);
t_matrix        matrix_mult_matrix(t_matrix m1, t_matrix m2);
void        init_matrix_translation(t_matrix *m, float x, float y, float z);
void        init_matrix_identity(t_matrix *m);
void			quickinversematrix(t_matrix *mat, t_matrix mat_pointat);
void			pointatmatrix(t_matrix *matrix, t_vec pos, t_vec target, t_vec up);
t_triangle          matrix_mult_triangle(t_matrix m, t_triangle tri);

/*
**Vector calcul
*/

t_vec           matrix_mult_vector(t_matrix m, t_vec i);
t_vec           vectoradd(t_vec v1, t_vec v2);
t_vec           vectorsub(t_vec v1, t_vec v2);
float           vectorproduct(t_vec v1, t_vec v2);
t_vec           vectornormal(t_vec v);
t_vec           vectorcrossprod(t_vec v1, t_vec v2);
t_vec           vectordiv(t_vec v, float a);
t_vec           vectormult(t_vec v, float a);
float           vectorlen(t_vec v);

/*
**Triangle Draw
*/

void        fill_triangle(t_env *e, t_triangle tri, int color);
void        draw_triangle(t_env *e, t_triangle t);

void        put_pixel(t_env *e, int x, int y, int color);

/*
**Events
*/

void        event(t_env *env);

void        back_to_env(t_env *e, t_vec vec[3], int i);

/*
**Color
*/

t_rgba      hex_to_rgba(int c);
int         rgba_to_hex(t_rgba rgba);
int         color_shading(int color, float shade);

#endif