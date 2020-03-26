/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_tris.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 01:08:25 by saneveu           #+#    #+#             */
/*   Updated: 2020/03/19 21:59:49 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

static void     sort_orthogonal(t_triangle *t)
{
    if (t->p[1].y < t->p[0].y)
    {
        ft_fswap(&t->p[0].x, &t->p[1].x);
        ft_fswap(&t->p[0].y, &t->p[1].y);
        ft_fswap(&t->tx[0].u,&t->tx[1].u);
        ft_fswap(&t->tx[0].v,&t->tx[1].v);
        ft_fswap(&t->tx[0].w,&t->tx[1].w);
    }
    if (t->p[2].y < t->p[0].y)
    {
        ft_fswap(&t->p[2].x, &t->p[0].x);
        ft_fswap(&t->p[2].y, &t->p[0].y);
        ft_fswap(&t->tx[2].u, &t->tx[0].u); 
        ft_fswap(&t->tx[2].v, &t->tx[0].v); 
        ft_fswap(&t->tx[2].w, &t->tx[0].w); 
    }
    if (t->p[2].y < t->p[1].y)
    {
        ft_fswap(&t->p[2].x, &t->p[1].x);
        ft_fswap(&t->p[2].y, &t->p[1].y);
        ft_fswap(&t->tx[2].u,&t->tx[1].u); 
        ft_fswap(&t->tx[2].v,&t->tx[1].v); 
        ft_fswap(&t->tx[2].w,&t->tx[1].w); 
    }
}
static void     texture_p_image(t_env *e, t_filltex *f, t_triangle *tri, int i)
{
    float   tstep;
    float   t;
    float   j;

    f->tex_u = f->su;
    f->tex_v = f->sv;

    tstep = 1.0f / ((float)(f->bx - f->ax));
    t = 0.0f;
    j = f->ax - 1;
    while (++j < f->bx)
    {
        //printf("j = %f\n", j);
        f->tex_u = (1.0f - t) * f->su + t * f->eu;
        f->tex_v = (1.0f - t) * f->sv + t * f->ev;
        f->tex_w = (1.0f - t) * f->sw + t * f->ew;
        //put_pixel(e, i, j, get_pixel(e->txt[0].sprite, f->tex_u, f->tex_v));
        t += tstep;
    }

}

static void     fill_triangle_texture_2bis(t_env *e, t_filltex *f, t_triangle *t)
{
    int i;

    i = 0;
    if (f->dy1)
    {
        printf("1\n");
        f->dax_s = f->dx1 / f->dy1;
        f->du1_s = f->du1 / f->dy1;
        f->dv1_s = f->dv1 / f->dy1;
        f->dw1_s = f->dw1 / f->dy1;
    }
    if (f->dy2)
    {
        printf("2\n");
        f->dbx_s = f->dx2 / f->dy2;
        f->du2_s = f->du2 / f->dy2;
        f->dv2_s = f->dv2 / f->dy2;
        f->dw2_s = f->dw2 / f->dy2;

    }
    i = t->p[1].y - 1;
    while (++i <= t->p[2].y)
    {
        printf("3\n");
        f->ax = t->p[1].x + (float)(i - t->p[1].y) * f->dax_s; 
        f->bx = t->p[0].x + (float)(i - t->p[0].y) * f->dbx_s;
        printf("ax = %d     bx = %d\n", f->ax, f->bx);
 
        f->su = t->tx[1].u + (float)(i - t->p[1].y) * f->du1_s; 
        f->sv = t->tx[1].v + (float)(i - t->p[1].y) * f->dv1_s;
        f->sw = t->tx[1].w + (float)(i - t->p[1].y) * f->dv1_s;
        f->eu = t->tx[0].u + (float)(i - t->p[0].y) * f->du2_s; 
        f->ev = t->tx[0].v + (float)(i - t->p[0].y) * f->dv2_s;
        f->ew = t->tx[0].w + (float)(i - t->p[0].y) * f->dw2_s; 
        if (f->ax > f->bx)
        {
            ft_swap((void*)&f->ax, (void*)&f->bx);
            ft_swap((void*)&f->su, (void*)&f->eu);
            ft_swap((void*)&f->sv, (void*)&f->ev);
            ft_swap((void*)&f->sw, (void*)&f->ew);
        }
        //texture_p_image(e, f, t, i);
    }
}

static void     fill_triangle_texture_2(t_env *e, t_filltex *f, t_triangle *t)
{
    int i;

    i = 0;
    if (f->dy1)
    {
        printf("1\n");
        f->dax_s = f->dx1 / f->dy1;
        f->du1_s = f->du1 / f->dy1;
        f->dv1_s = f->dv1 / f->dy1;
        f->dw1_s = f->dw1 / f->dy1;
    }
    if (f->dy2)
    {
        printf("2\n");
        f->dbx_s = f->dx2 / f->dy2;
        f->du2_s = f->du2 / f->dy2;
        f->dv2_s = f->dv2 / f->dy2;
        f->dw2_s = f->dw2 / f->dy2;

    }
    if (f->dy1)
    {
        printf("3\n");

        i = t->p[0].y - 1;
        printf("start %f\nend %f\n", t->p[0].y, t->p[1].y);
        while (++i <= t->p[1].y)
        {
            f->ax = t->p[0].x + (float)(i - t->p[0].y) * f->dax_s; 
            f->bx = t->p[0].x + (float)(i - t->p[0].y) * f->dbx_s;
        printf("ax = %d     bx = %d\n", f->ax, f->bx);        
            f->su = t->tx[0].u + (float)(i - t->p[0].y) * f->du1_s; 
            f->sv = t->tx[0].v + (float)(i - t->p[0].y) * f->dv1_s;
            f->sw = t->tx[0].w + (float)(i - t->p[0].y) * f->dv1_s;

            f->eu = t->tx[0].u + (float)(i - t->p[0].y) * f->du2_s; 
            f->ev = t->tx[0].v + (float)(i - t->p[0].y) * f->dv2_s;
            f->ew = t->tx[0].w + (float)(i - t->p[0].y) * f->dw2_s; 

            if (f->ax > f->bx)
            {
                ft_fswap((float*)&f->ax, (float*)&f->bx);
                ft_fswap(&f->su, &f->eu);
                ft_fswap(&f->sv, &f->ev);
            }
            //texture_p_image(e, f, t, i);
        }
    }
}

void            fill_triangle_texture(t_env *e, t_triangle t)
{
    t_filltex   fill;
    
    ft_memset(&fill, 0, sizeof(t_fill));
    //printf("===============START==============================\n");
    sort_orthogonal(&t);
    fill.dy1 = t.p[1].y - t.p[0].y;
    fill.dx1 = t.p[1].x - t.p[0].x;
    fill.du1 = t.tx[1].u - t.tx[0].u;
    fill.dv1 = t.tx[1].v - t.tx[0].v;
    //fill.dw1 = t.tx[1].w - t.tx[0].w;

    fill.dy2 = t.p[2].y - t.p[0].y;
    fill.dx2 = t.p[2].x - t.p[0].x;
    fill.du2 = t.tx[2].u - t.tx[0].u;
    fill.dv2 = t.tx[2].v - t.tx[0].v;
    //printf("u %f v %f w %f\n", t.tx[2].u, t.tx[2].v, t.tx[2].w);
    //printf("x %f y %f z %f\n", t.p[2].x, t.p[2].y, t.p[2].z);
    //fill.dw2 = t.tx[2].w - t.tx[0].w;
    printf("\n----<> Enter Fille triangle Phase 1\n");
    fill_triangle_texture_2(e, &fill, &t);
    printf("\n----<> Out\n");
    fill.dy1 = t.p[2].y - t.p[1].y;
    fill.dx1 = t.p[2].x - t.p[1].x;
    fill.du1 = t.tx[2].u - t.tx[1].u;
    fill.dv1 = t.tx[2].v - t.tx[1].v;
    //fill.dv1 = t.tx[2].w - t.tx[1].w;
    printf("\n----<> Enter Fille triangle Phase 2\n");
    fill_triangle_texture_2bis(e, &fill, &t);
    printf("\n----<> Out\n");
}