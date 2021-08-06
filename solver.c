/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 10:22:49 by skoskine          #+#    #+#             */
/*   Updated: 2020/08/03 11:21:12 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
** Prints the square in a correct form.
*/

static int	ft_print_square(char *result, int square_size)
{
	int j;
	int i;

	j = 0;
	while (j < square_size)
	{
		i = 0;
		while (i < square_size)
		{
			ft_putchar(result[square_size * j + i]);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
	return (1);
}

/*
** Returns the index of the next mino (starting from index i)
** that has not already been added to the square. If all have been
** added, it returns the index of the terminating NULL pointer.
*/

static int	ft_next_to_add(t_mino **minos, int i)
{
	while (minos[i] != NULL)
	{
		if (minos[i]->added == 0)
			return (i);
		i++;
	}
	return (i);
}

/*
** Ft_solver implements a backtracking algorithm to find the first possible
** arrangement of all given tetriminos in the given square. It first saves to i
** the index of the first mino which has not yet been added to the square.
** If it encounters the stopping condition (all minos have already been added),
** it calls ft_print_square to print the result square and returns 1. Otherwise,
** ft_add is called in a loop to find the next available slot for the given mino
** and add it in the square. If the recursive call of ft_solve does not find a
** solution, the mino is removed from the square and ft_add is called again to
** try next available position (if exists). If no result exists for the given
** square size, 0 is returned.
*/

static int	ft_solve(t_mino **minos, char *sqr, int size)
{
	int i;
	int count;

	i = ft_next_to_add(minos, 0);
	if (minos[i] == NULL)
		return (ft_print_square(sqr, size));
	count = 0;
	while (ft_add(sqr, minos[i], size, count) != 0)
	{
		if ((ft_solve(minos, sqr, size)) == 1)
			return (1);
		ft_remove(sqr, minos[i]);
		count++;
	}
	return (0);
}

/*
** Initializes the char array for the square in which tetriminos are placed.
*/

static char	*ft_init_square(int square_size)
{
	char	*square;

	square = (char*)malloc(sizeof(char) * (square_size * square_size + 1));
	if (!square)
		return (NULL);
	ft_memset(square, '.', square_size * square_size);
	square[square_size * square_size] = '\0';
	return (square);
}

/*
** After calculating the starting size of the square and initializing the square
** and result arrays, ft_solve is called until it finds a solution. If that does
** not return a solution, the square size is increased. Finally,
** the result square is freed and the final square size returned.
*/

int			ft_fillit(t_mino **minos)
{
	int		size;
	int		square_size;
	char	*square;

	size = 0;
	while (minos[size] != NULL)
		size++;
	square_size = 2;
	while (square_size * square_size < size * 4)
		square_size++;
	if (!(square = ft_init_square(square_size)))
		return (0);
	while (ft_solve(minos, square, square_size) != 1)
	{
		free(square);
		square_size++;
		if (!(square = ft_init_square(square_size)))
			return (0);
	}
	free(square);
	return (square_size);
}
