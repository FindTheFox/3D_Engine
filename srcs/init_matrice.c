/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 02:29:46 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:22:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

void       init_matrix_rotz(t_matrix *m, float theta)
{
    m->m[0][0] = cosf(theta);
    m->m[0][1] = sinf(theta);
    m->m[1][0] = -sinf(theta);
    m->m[1][1] = cosf(theta);
    m->m[2][2] = 1;
    m->m[3][3] = 1;
}

void        init_matrix_rotx(t_matrix *m, float theta)
{
    m->m[0][0] = 1;
    m->m[1][1] = cosf(theta);
    m->m[1][2] = sinf(theta);
    m->m[2][1] = -sinf(theta);
    m->m[2][2] = cosf(theta);
    m->m[3][3] = 1;
}

void        init_matrix_roty(t_matrix *m, float theta)
{
    m->m[0][0] = cosf(theta);
    m->m[0][2] = sinf(theta);
    m->m[2][0] = -sinf(theta);
    m->m[1][1] = 1.0f;
    m->m[2][2] = cosf(theta);
    m->m[3][3] = 1.0f;
}

void       init_matrix_translation(t_matrix *m, float x, float y, float z)
{
    m->m[1][1] = 1.0f;
    m->m[0][0] = 1.0f;
    m->m[2][2] = 1.0f;
    m->m[3][3] = 1.0f;
    m->m[3][0] = x;
    m->m[3][1] = y;
    m->m[3][2] = z;
}

void            init_matrix_identity(t_matrix *m)
{
    m->m[0][0] = 1.0f;
    m->m[1][1] = 1.0f;
    m->m[2][2] = 1.0f;
    m->m[3][3] = 1.0f;
}

void            init_matrix_proj(t_env *e)
{
    e->mlist.matproj.m[0][0] = e->fAspectRatio * e->fFovRad;
    e->mlist.matproj.m[1][1] = e->fFovRad;
    e->mlist.matproj.m[2][2] = e->fFar / (e->fFar - e->fNear);
    e->mlist.matproj.m[3][2] = (-e->fFar * e->fNear) / (e->fFar - e->fNear);
    e->mlist.matproj.m[2][3] = 1.0f;
}

t_matrix        matrix_mult_matrix(t_matrix m1, t_matrix m2)
{
    t_matrix m;
    int i;
    int j;

    i = -1;
    while (++i < 4)
    {
        j = -1;
        while (++j < 4)
            m.m[j][i] = m1.m[j][0] * m2.m[0][i]
            + m1.m[j][1] * m2.m[1][i]
            + m1.m[j][2] * m2.m[2][i]
            + m1.m[j][3] * m2.m[3][i];
    }
    return (m);
}

void			quickinversematrix(t_matrix *mat, t_matrix mat_pointat)
{
	mat->m[0][0] = mat_pointat.m[0][0];
	mat->m[0][1] = mat_pointat.m[1][0];
	mat->m[0][2] = mat_pointat.m[2][0];
	mat->m[1][0] = mat_pointat.m[0][1];
	mat->m[1][1] = mat_pointat.m[1][1];
	mat->m[1][2] = mat_pointat.m[2][1];
	mat->m[2][0] = mat_pointat.m[0][2];
	mat->m[2][1] = mat_pointat.m[1][2];
	mat->m[2][2] = mat_pointat.m[2][2];
	mat->m[3][0] = -(mat_pointat.m[3][0] * mat->m[0][0]
		+ mat_pointat.m[3][1] * mat->m[1][0] + mat_pointat.m[3][2] * mat->m[2][0]);
	mat->m[3][1] = -(mat_pointat.m[3][0] * mat->m[0][1]
		+ mat_pointat.m[3][1] * mat->m[1][1] + mat_pointat.m[3][2] * mat->m[2][1]);
	mat->m[3][2] = -(mat_pointat.m[3][0] * mat->m[0][2] 
        + mat_pointat.m[3][1] * mat->m[1][2] + mat_pointat.m[3][2] * mat->m[2][2]);
	mat->m[3][3] = 1;
}

void			pointatmatrix(t_matrix *matrix,	t_vec pos, t_vec target, t_vec up)
{
	t_vec	a;
	t_vec	forward;
	t_vec	right;

	forward = vectorsub(target, pos);
	forward = vectornormal(forward);
	a = vectormult(forward, vectorproduct(up, forward));
	up = vectorsub(up, a);
	right = vectorcrossprod(up, forward);
	matrix->m[0][0] = right.x;
	matrix->m[0][1] = right.y;
	matrix->m[0][2] = right.z;
	matrix->m[1][0] = up.x;
	matrix->m[1][1] = up.y;
	matrix->m[1][2] = up.z;
	matrix->m[2][0] = forward.x;
	matrix->m[2][1] = forward.y;
	matrix->m[2][2] = forward.z;
	matrix->m[3][0] = pos.x;
	matrix->m[3][1] = pos.y;
	matrix->m[3][2] = pos.z;
	matrix->m[3][3] = 1;
}

t_triangle          matrix_mult_triangle(t_matrix m, t_triangle tri)
{
    t_triangle triout;

    triout.p[0] = matrix_mult_vector(m, tri.p[0]);
    triout.p[1] = matrix_mult_vector(m, tri.p[1]);
    triout.p[2] = matrix_mult_vector(m, tri.p[2]);
    return (triout);
}
