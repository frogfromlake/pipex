/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 16:40:40 by fquist            #+#    #+#             */
/*   Updated: 2022/01/31 17:16:21 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	**pipes_arr_alloc(int n);

int	**create_pipes_arr(int n)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = pipes_arr_alloc(n);
	if (pipes == NULL)
		exit(ENOMEM);
	while (i < n)
	{
		if (pipe(pipes[i]) < 0)
		{
			perror(NULL);
			free_pipes_arr(pipes, n);
			exit(errno);
		}
		i++;
	}
	return (pipes);
}

static int	**pipes_arr_alloc(int n)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc(n * sizeof(int *));
	if (pipes == NULL)
		exit(ENOMEM);
	while (i < n)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
			exit(ENOMEM);
		i++;
	}
	return (pipes);
}

void	free_pipes_arr(int **arr, int elements)
{
	int	i;

	i = 0;
	while (i < elements)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	close_pipes(int **pipes, int childs, int child_nbr)
{
	int	i;
	int	rt_status;

	i = 0;
	rt_status = EXIT_SUCCESS;
	while (i < (childs - 1))
	{
		if (i != child_nbr)
		{
			rt_status = close(pipes[i][1]);
			pipes[i][1] = 0;
		}
		if (i != child_nbr - 1)
		{
			rt_status = close(pipes[i][0]);
			pipes[i][0] = 0;
		}
		i++;
	}
	return (rt_status);
}
