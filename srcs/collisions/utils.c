
#include "../../includes/3d_engine.h"
#include "../../includes/collide.h"

t_vec create_t_vec(float x, float y, float z)
{
    t_vec new;

    new.x = x;
    new.y = y;
    new.z = z;
    new.w = 1;
    return (new);
}

t_hitbox create_hitbox(t_vec min, t_vec max)
{
    t_hitbox new;

    new.min = min;
    new.max = max;
    return (new);
}

int is_y_collide(t_mesh obj1, t_mesh obj2)
{
    float lowbox1_y;
    float highbox1_y;
    float lowbox2_y;
    float highbox2_y;

    lowbox1_y = obj1.dir.y + obj1.hitbox.min.y;
    highbox1_y = obj1.dir.y + obj1.hitbox.max.y;
    lowbox2_y = obj2.dir.y + obj2.hitbox.min.y;
    highbox2_y = obj2.dir.y + obj2.hitbox.max.y;

    if (highbox1_y >= lowbox2_y && highbox2_y >= lowbox2_y)
        return (1);
    return (0);
}

t_line create_hit_line()
{
    
}

t_hit_lines create_hit_lines(t_mesh obj)
{

}

int is_xy_collide(t_mesh obj1, t_mesh obj2)
{

}

int is_collide(t_mesh obj1, t_mesh obj2)
{

}