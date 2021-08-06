/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoskine <skoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 10:54:50 by skoskine          #+#    #+#             */
/*   Updated: 2020/08/03 10:49:49 by skoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef struct	s_block
{
	int			x;
	int			y;
}				t_block;

typedef struct	s_mino
{
	t_block		block[4];
	char		pos;
	int			added;
}				t_mino;

int				ft_read_input(int fd, t_mino **minos);
int				ft_fillit(t_mino **minos);
int				ft_add(char *square, t_mino *mino, int size, int count);
void			ft_remove(char *square, t_mino *mino);

#endif
