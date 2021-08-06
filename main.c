/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 16:49:17 by skoskine          #+#    #+#             */
/*   Updated: 2020/08/03 11:20:17 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"
#include <fcntl.h>

/*
** Prints an error message and returns EXIT_FAILURE for main to return.
*/

static int	ft_exit_foobar(void)
{
	ft_putstr("error\n");
	return (EXIT_FAILURE);
}

/*
** Prints a usage message and returns EXIT_FAILURE for main to return.
*/

static int	ft_exit_usage(void)
{
	ft_putstr("usage: ./fillit input_file\n");
	return (EXIT_FAILURE);
}

/*
** Calculates the size of an array of pointers terminated by a NULL pointer.
*/

static int	ft_arr_size(void **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
** The program first checks that it has been given one file as argument
** that can be opened. The array in which to save the tetriminos is
** initialized, input is read from fd, and if it is valid it is saved
** in the array. The array is then passed on to ft_solve which does the heavy
** lifting, prints the result, and returns the square size of the solution.
** Finally, remaining allocated memory is freed.
*/

int			main(int argc, char **argv)
{
	int		fd;
	int		square_size;
	t_mino	**tetriminos;

	if (argc != 2)
		return (ft_exit_usage());
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (ft_exit_foobar());
	if (!(tetriminos = (t_mino**)malloc(sizeof(t_mino*) * (26 + 1))))
		return (ft_exit_foobar());
	if (ft_read_input(fd, tetriminos) == EXIT_FAILURE)
	{
		free(tetriminos);
		return (ft_exit_foobar());
	}
	square_size = ft_fillit(tetriminos);
	ft_free_array((void***)&tetriminos, ft_arr_size((void**)tetriminos));
	if (square_size == 0)
		return (ft_exit_foobar());
	return (0);
}
