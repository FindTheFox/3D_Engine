#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "../libft/includes/libft.h"

typedef struct s_attr_lst
{
	t_list		*v;
	t_list		*vt;
	t_list		*vn;
	int			v_size;
	int			vt_size;
	int			vn_size;
}				t_attr_lst;


# endif