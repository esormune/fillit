/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 15:26:02 by skoskine          #+#    #+#             */
/*   Updated: 2020/07/27 19:00:28 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_free_array(void ***array, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
