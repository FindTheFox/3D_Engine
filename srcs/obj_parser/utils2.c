/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/03 23:16:04 by saneveu           #+#    #+#             */
/*   Updated: 2020/04/27 20:23:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/obj_parser.h"

char	*ft_fatoi_ptr(char *str, float *value)
{
	float	nb;
	float	pow;
	int		neg;

	nb = 0;
	neg = 1;
	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		str++ && (neg = -1);
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*(str++) - '0');
	if (*str == '.')
	{
		str++;
		pow = 0.1;
		while (*str >= '0' && *str <= '9' && pow > 0.00001)
		{
			nb += (*(str++) - '0') * pow;
			pow /= 10;
		}
	}
	*value = nb * neg;
	return (str);
}

char	*ft_atoi_ptr(char *str, int *value)
{
	int	nb;
	int	neg;

	nb = 0;
	neg = 1;
	while ((*str < 14 && *str > 8) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		str++ && (neg = -1);
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + (*(str++) - '0');
	*value = nb * neg;
	return (str);
}

t_triangle triangle_init(void)
{
	t_triangle	new;
	t_vec		vec;
	t_vec2d		tex;
	int			i;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	vec.w = 1;
	tex.u = 0;
	tex.v = 0;
	tex.w = 1;
	new.color = 0;
	i = 0;
	while (i < 3)
	{
		new.p[i] = vec;
		new.tx[i] = tex;
		i++;
	}
	return (new);
}

void init_key_list(t_attr_lst *key_list)
{
	key_list->v = NULL;
	key_list->vt = NULL;
	key_list->vn = NULL;
	key_list->v_size = 0;
	key_list->vt_size = 0;
	key_list->vn_size = 0;
	key_list->tris_curr_id = 0;
	key_list->tris_size = FACES_ARRAY_SIZE;
	key_list->tris = (t_triangle*)malloc(sizeof(t_triangle) * FACES_ARRAY_SIZE);
}

void assign_from_array(void *data, int length, float *values)
{
	float *to_assign;
	int i;

	to_assign = (float*)data;
	i = 0;
	while (i < length)
	{
		to_assign[i] = values[i];
		i++;
	}
}
