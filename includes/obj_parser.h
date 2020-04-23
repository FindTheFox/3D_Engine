#ifndef OBJ_PARSER_H
# define OBJ_PARSER_H

# include "../libft/includes/libft.h"
# include "3d_engine.h"

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

void		create_triangle_list(t_attr_lst *key_list);
void		assign_from_array(void *data, int length, float *values);
void		init_key_list(t_attr_lst *key_list);
t_triangle	triangle_init(void);
char		*ft_atoi_ptr(char *str, int *value);
char		*ft_fatoi_ptr(char *str, float *value);
void		print_array(float **array, int size, int content_size, char *name);
void		print_faces_content(t_triangle *tris, int size);
void		print_t_list(t_list *list);
char		*skip_until_num(char *str);
char		*skip_until_space(char *str);
void		*double_array_size(void *data, int unit_size, size_t array_length);

# endif