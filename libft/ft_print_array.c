/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:57:04 by skoskine          #+#    #+#             */
/*   Updated: 2020/07/28 15:06:19 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		ft_putendl(array[i++]);
}
