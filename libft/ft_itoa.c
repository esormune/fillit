/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 18:08:36 by esormune          #+#    #+#             */
/*   Updated: 2020/06/18 17:34:02 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

static char	*ft_create_string(long n, int len)
{
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	len--;
	while (len >= 0)
	{
		dest[len] = 48 + (n % 10);
		n = n / 10;
		len--;
	}
	return (dest);
}

static char	*ft_create_negstring(long n, int len)
{
	char	*dest;

	if (!(dest = (char*)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	dest[len + 1] = '\0';
	dest[0] = '-';
	while (len > 0)
	{
		dest[len] = 48 + (n % 10);
		n = n / 10;
		len--;
	}
	return (dest);
}

static int	ft_size(long n)
{
	int		count;

	count = 0;
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	count++;
	return (count);
}

static int	ft_is_neg(long n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char		*ft_itoa(int n)
{
	char	*dest;
	int		neg;
	int		len;
	long	nb;

	nb = n;
	neg = ft_is_neg(nb);
	if (neg == 1)
	{
		nb = nb * (-1);
		len = ft_size(nb);
		if (!(dest = ft_create_negstring(nb, len)))
			return (NULL);
	}
	else if (neg == 0)
	{
		len = ft_size(nb);
		if (!(dest = ft_create_string(nb, len)))
			return (NULL);
	}
	else
		return (NULL);
	return (dest);
}
