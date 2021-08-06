/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 13:29:23 by skoskine          #+#    #+#             */
/*   Updated: 2020/08/03 11:30:55 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

/*
** Checks that for each of the mino's coordinates there exists a valid
** coordinate (starting from the given point) and that coordinate
** is empty.
*/

static int	ft_check(char *sqr, t_mino *mino, int i, int j)
{
	int	n;
	int	size;

	n = 1;
	size = 2;
	while (sqr[size * size] != '\0')
		size++;
	while (n < 4)
	{
		if (!(j + mino->block[n].y < size && j + mino->block[n].y >= 0 &&
			i + mino->block[n].x < size && i + mino->block[n].x >= 0 &&
			sqr[size * (j + mino->block[n].y) + i + mino->block[n].x] == '.'))
			break ;
		n++;
	}
	if (n == 4)
		return (1);
	return (0);
}

/*
** Sets the mino's letter to the correct coordinates.
*/

static int	ft_fill(char *square, t_mino *mino, int i, int j)
{
	int	size;

	size = 2;
	while (square[size * size] != '\0')
		size++;
	square[size * (j + mino->block[0].y) + i + mino->block[0].x] = mino->pos;
	square[size * (j + mino->block[1].y) + i + mino->block[1].x] = mino->pos;
	square[size * (j + mino->block[2].y) + i + mino->block[2].x] = mino->pos;
	square[size * (j + mino->block[3].y) + i + mino->block[3].x] = mino->pos;
	mino->added = 1;
	return (1);
}

/*
** Loops through the square and calls ft_check for each empty slot whether
** the given mino could be added starting from those coordinates. If so,
** ft_fill is called to assign the mino's letter to these coordinates and
** to return 1. If count > 0, that many available slots must be skipped
** before the mino is added. If there are no more available slots, 0 is
** returned.
*/

int			ft_add(char *square, t_mino *mino, int size, int count)
{
	int	i;
	int	j;
	int ret;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			if (square[size * j + i] == '.')
			{
				if ((ret = ft_check(square, mino, i, j)) == 1 && count == 0)
					return (ft_fill(square, mino, i, j));
				else if (ret == 1 && count > 0)
					count--;
			}
			if (++i + mino->block[3].x >= size)
				break ;
		}
		if (++j + mino->block[3].y >= size)
			break ;
	}
	return (0);
}

/*
** Replaces the given mino's letters with '.' in the square.
*/

void		ft_remove(char *square, t_mino *mino)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	mino->added = 0;
	while (square[i] != '\0')
	{
		if (square[i] == mino->pos)
		{
			square[i] = '.';
			n++;
		}
		if (n == 4)
			return ;
		i++;
	}
}
