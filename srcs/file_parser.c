/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 20:13:44 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/19 20:22:16 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/3d_engine.h"

static void        get_vertex(t_env *e, int x)
{
    float v[3];
    int i;
    int vcount;

    vcount = 0;
    while (vcount < 3 && e->parse.str[x] && e->parse.str[x] != '\n')
    {
        if (e->parse.str[x] == ' ' || e->parse.str[x] == '-')
            ++x;
        else if (ft_isdigit(e->parse.str[x]))
        {
            v[vcount++] = atof(e->parse.str + x - 1);
            while (ft_isdigit(e->parse.str[x]) || e->parse.str[x] == '.')
                ++x;
        }
        else if (e->parse.str[x])
            ft_exit(e, "parse vertex error", 0);
    }
    e->parse.vertex[e->parse.vi++] = (t_vec){ v[0], v[1], v[2], 1 };
}

static int      malloc_size(t_env *e, int start, char end, char c)
{
    int ret;

    ret = -1;
    while (e->parse.str && e->parse.str[start])
    {
        if (e->parse.str[start] == c)
        {
            while (e->parse.str && e->parse.str[start] && e->parse.str[start] != '\n')
                start++;
            ++ret;
            if (e->parse.str[++start] == c)
                continue ;
            else if (e->parse.str[start] == end)
                return (ret + 1);
            else
                ft_exit(e, "Invalid File1", 0);
        }
        else
            ft_exit(e, "Invalid File2", 0);
    }
    return (ret);
}

static void     get_triangle(t_env *e, int x, int mi)
{
    int         nb;
    int         vi[3];

    nb = 0;
    while (nb < 3 && e->parse.str && e->parse.str[x])
    {
        if (e->parse.str[x] == ' ')
            ++x;
        else if (ft_isdigit(e->parse.str[x]))
        {
           vi[nb++] = atoi(e->parse.str + x - 1); 
           while (ft_isdigit(e->parse.str[x]))
                ++x;
        }
        else if (e->parse.str[x])
            ft_exit(e, "Invalid Filer", 0);
    }
    e->mesh[mi].size = e->parse.ti;
    e->mesh[mi].tris[e->parse.ti++] = (t_triangle){ 
        e->parse.vertex[vi[0] - 1],
        e->parse.vertex[vi[1] - 1],
        e->parse.vertex[vi[2] - 1] };
}

static void     check_triangle(t_env *e, int x, int i, int mi)
{
    e->parse.fnb = malloc_size(e, x, '\0', 'f');
    if (!(e->mesh[mi].tris = (t_triangle *)ft_memalloc(sizeof(t_triangle)
            * e->parse.fnb)))
        ft_exit(e, "Malloc Mesh Error", 0);
    while (e->parse.str && e->parse.str[x])
    {
        if (e->parse.str[x] == 'f')
        {
            i = x + 2;
            while (e->parse.str && e->parse.str[x] && e->parse.str[x] != '\n')
                ++x;
            if (e->parse.str[++x] == 'f')
                get_triangle(e, i, mi);
            else if (e->parse.str[x] == '\n' || e->parse.str[x] == '\0')
                return (get_triangle(e, i, mi));
            else
                ft_exit(e, "Invalid File3", 0);
        }
        else
            ft_exit(e, "Invalid File4", 0);
    }
}

static void     get_mesh(t_env *e, int mi)
{
    int x;
    int i;

    x = 0;
    while (e->parse.str[x] && e->parse.str)
    {
        if (e->parse.str[x] == 'v')
        {
            i = x + 2;
            while (e->parse.str && e->parse.str[x] && e->parse.str[x] != '\n')
                x++;
            if (e->parse.str[++x] == 'v')
                get_vertex(e, i);
            else if (e->parse.str[x] == '\n')
            {
                get_vertex(e, i);
                return(check_triangle(e, x + 1, i, mi));
            }
            else
                ft_exit(e, "Parse Mesh Error1", 0);
        }
        else
            ft_exit(e, "Parse Mesh Error", 0);
    }
}

void            file_parser(t_env *e, char *file, int mi)
{
    if (!(e->parse.str = ft_readfile(file)))
        ft_exit(e, "read error", 0);
    e->parse.vnb = malloc_size(e, 0, '\n', 'v');
    if (!(e->parse.vertex = (t_vec *)ft_memalloc(sizeof(t_vec) * e->parse.vnb)))
        ft_exit(e, "Parser Vertex malloc error", 0);
    e->parse.ti = 0;
    e->parse.vi = 0;
    get_mesh(e, mi);
    ft_memdel((void **)&e->parse.vertex);
    ft_strdel(&e->parse.str);
}
