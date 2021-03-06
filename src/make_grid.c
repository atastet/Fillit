/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atastet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:14:59 by atastet           #+#    #+#             */
/*   Updated: 2018/07/03 20:18:02 by atastet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fillit.h"

/*
** Writes a tetrimino on a place (x, y) with the good letter associated
*/

static void	write_tet(t_tetrimino *lst, char **grid, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < lst->height)
	{
		j = 0;
		while (j < lst->width)
		{
			if (lst->tetrimino[i][j] == '#')
				grid[y + i][x + j] = lst->letter;
			j++;
		}
		i++;
	}
}

static void	write_point(t_tetrimino *lst, char **grid, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < lst->height)
	{
		j = 0;
		while (j < lst->width)
		{
			if (lst->tetrimino[i][j] == '#')
				grid[y + i][x + j] = '.';
			j++;
		}
		i++;
	}
}

/*
** Test if a Tetrimino can be placed on the map at a set place (x, y)
** Writes it on the place if it is possible
*/

static int	set_tet(t_tetrimino *lst, char **grid, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < lst->height)
	{
		j = 0;
		while (j < lst->width)
		{
			if (lst->tetrimino[i][j] == '#' && grid[y + i][x + j] != '.')
				return (0);
			j++;
		}
		i++;
	}
	write_tet(lst, grid, x, y);
	return (1);
}

static int	solve_grid(char **grid, t_tetrimino *lst, int size_grid)
{
	int			i;
	int			j;
	t_tetrimino	*tet;

	i = 0;
	tet = lst;
	if (lst == NULL)
		return (1);
	while (i < size_grid - lst->height)
	{
		j = 0;
		while (j < size_grid - lst->width)
		{
			if (set_tet(tet, grid, j, i) == 1)
			{
				if (solve_grid(grid, tet->next, size_grid) == 1)
					return (1);
				else
					write_point(tet, grid, j, i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char		**make_grid(t_tetrimino *lst, int size_grid)
{
	char		**grid;
	int			size;

	size = size_grid;
	if ((grid = (char**)malloc(sizeof(char*) * size)) == NULL)
		return (NULL);
	grid = fill_grid_point(grid, size);
	while (solve_grid(grid, lst, size) == 0)
	{
		size++;
		grid = fill_grid_point(grid, size);
	}
	return (grid);
}
