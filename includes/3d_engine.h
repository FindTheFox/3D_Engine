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
# include <pthread.h>

# include "texturing.h"

# define W_W 800
# define W_H 800

# define NTXT 1                 // Nombre de texture SDL_Surface
# define NSPRITE 0              // Nombre de sprites SDL_Surface

# define MIN_TO_CLIP 256
# define MIN_TO_RASTER 16384

# define NB_THREAD 32

# define KEY_NB 29
# define W 0
# define A 1
# define S 2
# define D 3
# define E 4
# define Q 5
# define UP 6
# define DOWN 7
# define LEFT 16
# define RIGHT 17
# define R 8
# define F 9
# define NUM1 14
# define NUM2 11
# define NUM3 15
# define NUM4 12
# define NUM5 20
# define NUM6 13
# define NUM7 22
# define NUM8 10
# define NUM9 23
# define MOUSE 18
# define SPACE 19
# define LCTRL 21
# define NUM0 24
# define PAD_ENTER 25
# define PLUS 26
# define MINUS 27
# define SHIFT 28
//DEFINE TEST MENU
# define EXIT_MENU 0
# define MAIN_MENU 1
# define PAUSE_MENU 2
# define CONTROLS_MENU 3
# define BUTTON_MARGE 6

typedef struct      s_image
{
    SDL_Surface     *sprite;
}                   t_image;

typedef struct      s_line
{
	int		lenght;
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		i;
	double	mix;
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

typedef struct      s_vec2d
{
    float   u;
    float   v;
    float   w;
}                   t_vec2d;

typedef struct      s_clip
{
    t_vec       in[3];
    t_vec2d     tx_in[3];
    t_vec       out[3];
    t_vec2d     tx_out[3];
    int         inside;
    int         tx_inside;
    int         outside;
    int         tx_outside;
    float       d[3];
    float       t;
}                   t_clip;

typedef struct      s_thread
{
    void            *env;
    pthread_t       thread;
    t_dyntab        tris;
    int             start;
    int             end;
    int             i;
    int             id;
}                   t_thread;

typedef struct      s_triangle
{
    t_vec   p[3];
    t_vec2d tx[3];
    int     color;
}                   t_triangle;

typedef struct      s_matrix
{
    float           m[4][4];
}                   t_matrix;

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
    SDL_Surface     *img;
    char            *name;          //FREE ?
}                   t_mesh;


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

typedef struct              s_usr
{
    int                     event_i_mesh;
    int                     opt_mesh;
    int                     shift;
}                           t_usr;

typedef struct              s_color
{
    int                     *tab;
}                           t_color;

typedef struct              s_env
{
    float                   ytheta;
    float                   xtheta;
    float                   ztheta;
    float                   theta;
    float                   zoom;
    float                   fNear;
    float                   fFar;
    float                   fFov;
    float                   fAspectRatio;
    float                   fFovRad;
    float                   fps;
    float                   time;
    float                   frametime;
    float                   yaw;
    float                   xaw;
    int                     wx;
    int                     wy;
    int                     key[KEY_NB];
    t_dyntab                clip_tab[4];
    t_dyntab                to_clip;
    t_dyntab                to_raster;
    t_vlist                 vlist;
    t_mlist                 mlist;
    t_fill                  fill;
    t_mesh                  *mesh;
    int                     nbmesh;
    int                     mesh_id;
    t_usr                   usr;
    t_color                 color;
    t_rgba                  rgba;
    t_line                  line;
    t_image                 txt[NTXT];
    SDL_MouseMotionEvent    mouse;
    SDL_Window              *window;
    SDL_Event               event;
    SDL_Renderer            *rend;
    SDL_Texture             *screen;
    SDL_Surface             *winsurf;
    SDL_Texture             *menu1;
    SDL_Texture             *menu2;
    SDL_Texture             *menu3;
    SDL_Surface             *tmp;
}                           t_env;

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
void        init_dynamic_tab(t_env *e);
void        rasterizer(t_env *e, t_dyntab *to_clip);
t_mesh      obj_parser(char *file, t_env *e);
void        matrix_view(t_env *e);
void        matrix_world(t_env *e, float xtheta, float ytheta, float ztheta);
int         lumiere(t_env *e, t_vec normal);
void        center(t_vec *out);

/*
**Clipping
*/

int         clip_triangle_by_plane(t_vec plane_n, t_vec plane_p, t_triangle in, t_triangle out[2]);
void        take_texture_vec(t_triangle *v1, t_triangle v2);
void        clip_mesh(t_env *e, t_dyntab *to_clip, t_dyntab *to_raster);

/*
**Matrice calcul and init
*/

void        init_matrix_proj(t_env *e);
void        init_matrix_rotx(t_matrix *m, float theta);
void        init_matrix_rotz(t_matrix *m, float theta);
void        init_matrix_roty(t_matrix *m, float theta);
t_matrix        matrix_mult_matrix(t_matrix m1, t_matrix m2);
void        init_matrix_translation(t_matrix *m, t_vec v);
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
float           distance_to_plane(t_vec plane_p, t_vec plane_n, t_vec p);
t_vec           vec_inter_plane(t_vec vec[2], t_vec linestart, t_vec lineend, float *t_out);
void            swap_vec(t_vec *v1, t_vec *v2);
/*
**Triangle Draw
*/

void        fill_triangle(t_env *e, t_triangle *tri, int color);
void        draw_triangle(t_env *e, t_triangle t);
void        ft_line(t_env *e, t_vec v1, t_vec v2, int color);
void        put_pixel(t_env *e, int x, int y, int color);

/*
**Fill texture
*/

void            fill_triangle_texture(t_env *e, t_triangle t);
uint32_t		get_pixel(SDL_Surface *surface, float tx, float ty);

/*
**Events
*/

void        event(t_env *env);
void        camera_event(t_env *e);
void        mesh_rot_event(t_env *e, int event_i_mesh);
void        back_to_env(t_env *e, t_vec vec[3], int i);

/*
**Color
*/

t_rgba      hex_to_rgba(int c);
int         rgba_to_hex(t_rgba rgba);
int         color_shading(int color, float shade);
int         colorset(t_env *e, int i);

/*
**Threading
*/

void            thread_init(t_env *e, t_thread *thread);

#endif