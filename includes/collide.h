#ifndef COLLIDE_H
# define COLLIDE_H

# include "object.h"
# include <math.h>

# define INTER_TOLERANCE 0.001

typedef struct  s_point
{
    double x;
    double y;
}               t_point;

typedef struct  s_line
{
    t_point p1;
    t_point p2;
}               t_line;

typedef struct  s_hit_lines
{
    t_line  left;
    t_line  up;
    t_line  right;
    t_line  down;
}               t_hit_lines;

#endif