/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:08:25 by esormune          #+#    #+#             */
/*   Updated: 2020/08/03 11:18:46 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

/*
** Realigns the block coordinates to set the first block's coordinates to (0,0)
** and the remaining three's coordinates as relative to the first block.
*/

static int	ft_realign(t_mino **tetriminos)
{
	int	i;
	int	x;
	int	y;
	int	b;

	i = 0;
	while (tetriminos[i] != NULL)
	{
		b = 0;
		x = tetriminos[i]->block[0].x;
		y = tetriminos[i]->block[0].y;
		while (b < 4)
		{
			tetriminos[i]->block[b].x = tetriminos[i]->block[b].x - x;
			tetriminos[i]->block[b].y = tetriminos[i]->block[b].y - y;
			b++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
** Ft_save_mino recursively saves the coordinates of the tetrimino blocks.
** It first saves the coordinates of index i to block n passed as arguments.
** Then, if it has not already saved all the blocks, it checks whether there
** is an unsaved adjacent block on the right, down or on the left. If so,
** it calls itself with that index and n + 1.
*/

static int	ft_save_mino(char *temp, t_mino *tetrimino, int i, int n)
{
	tetrimino->block[n].x = i % 4;
	tetrimino->block[n].y = i / 4;
	if (n == 3)
		return (n);
	if (i + 1 < 16 && (i + 1) % 4 != 0 && temp[i + 1] == '#')
	{
		if (n == 0)
			n = ft_save_mino(temp, tetrimino, i + 1, n + 1);
		else if (n > 0 && (tetrimino->block[n - 1].x != (i + 1) % 4 ||
		tetrimino->block[n - 1].y != (i + 1) / 4))
			n = ft_save_mino(temp, tetrimino, i + 1, n + 1);
	}
	if (n != 3 && i + 4 < 16 && temp[i + 4] == '#')
		n = ft_save_mino(temp, tetrimino, i + 4, n + 1);
	if (n != 3 && i - 1 > 0 && i % 4 != 0 && temp[i - 1] == '#')
	{
		if (n > 0 && (tetrimino->block[n - 1].x != (i - 1) % 4 ||
		tetrimino->block[n - 1].y != (i - 1) / 4) && (n == 1 || (n > 1 &&
		(tetrimino->block[n - 2].x != (i - 1) % 4 ||
		tetrimino->block[n - 2].y != (i - 1) / 4))))
			n = ft_save_mino(temp, tetrimino, i - 1, n + 1);
	}
	return (n);
}

/*
** After a 4x4 square has been saved, ft_set_mino checks that it contains
** a potentially valid Tetrimino, initializes a mino and saves it to the given
** pointer to the tetriminos array, and calls ft_save_mino to check that
** the coordinates are valid and to save them in the created mino struct.
** If ft_save_mino could not find the four adjacent blocks to save the
** coordinates, EXIT_FAILURE is returned.
*/

static int	ft_set_mino(char *temp, t_mino **tetrimino, int index)
{
	int		i;
	int		blocks;

	i = 0;
	blocks = 0;
	while (temp[i] == '#' || temp[i] == '.')
	{
		if (temp[i] == '#')
			blocks++;
		i++;
	}
	if (temp[i] != '\0' || blocks != 4)
		return (EXIT_FAILURE);
	if (!(*tetrimino = (t_mino*)malloc(sizeof(t_mino))))
		return (EXIT_FAILURE);
	(*tetrimino)->pos = 'A' + index;
	(*tetrimino)->added = 0;
	i = 0;
	while (temp[i] != '#')
		i++;
	if (ft_save_mino(temp, *tetrimino, i, 0) != 3)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** Reads 4 lines at a time in buf, checking after each call of read that there
** is a newline at the right place. After that, the read input is passed to
** ft_set_mino which checks the input and saves it in the minos array. Next,
** it checks that if the EOF has not been reached, the next character read is
** a newline (empty line between minos) and that the number of minos read
** has not exceeded 26. After looping through the minos, it calls ft_realign
** which also returns EXIT_SUCCESS to the main.
*/

int			ft_read_input(int fd, t_mino **minos)
{
	int		ret;
	int		i;
	int		lines;
	char	buf[20];

	ret = 1;
	i = 0;
	while (ret == 1)
	{
		lines = 0;
		while (lines < 4 && (ret = read(fd, &buf[lines * 4], 5)) == 5)
		{
			if (buf[lines * 4 + 4] != '\n')
				return (EXIT_FAILURE);
			buf[lines++ * 4 + 4] = '\0';
		}
		if (ret < 5)
			return (EXIT_FAILURE);
		if (ft_set_mino(buf, &minos[i], i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((((ret = read(fd, buf, 1)) == 1) && (buf[0] != '\n')) || ++i >= 27)
			return (EXIT_FAILURE);
	}
	minos[i] = NULL;
	return (ft_realign(minos));
}
