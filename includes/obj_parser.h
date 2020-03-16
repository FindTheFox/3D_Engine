#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "../libft/includes/libft.h"
# include "../includes/3d_engine.h"

# define FACES_ARRAY_SIZE 2500

typedef struct s_attr_lst
{
	t_list		*v;
	t_list		*vt;
	t_list		*vn;
	t_triangle	*tris;
	int			tris_curr_id;
	int			tris_size;
	int			v_size;
	int			vt_size;
	int			vn_size;
	float		**vert;
	float		**text;
	float		**norm;
}				t_attr_lst;


# endif