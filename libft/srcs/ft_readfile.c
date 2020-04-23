/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 23:15:12 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/15 23:16:09 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_readfile(char *file)
{
	int		ret;
	int		x;
	char	buf[BUFF_SIZE + 1];
	char	*str;

	if (!file || BUFF_SIZE < 0)
		return ((void *)0);
	if (!(str = ft_strnew(1)))
		return ((void *)0);
	x = open(file, O_RDONLY);
	while ((ret = read(x, buf, BUFF_SIZE)))
	{
		if (ret == -1)
		{
			ft_strdel(&str);
			close(x);
			return ((void *)0);
		}
		buf[ret] = '\0';
		str = ft_strfjoin(str, buf, 1);
	}
	close(x);
	return (str);
}