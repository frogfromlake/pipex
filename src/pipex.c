/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:01:26 by fquist            #+#    #+#             */
/*   Updated: 2022/01/31 19:15:50 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int		status;
	int		childs;
	int		here_doc;
	pid_t	*pids;

	if (argc < 5)
		error_msg("\e[0;31mError\nUsage: ./pipex infile \"cmd1\" "
			"\"cmd2\" outfile\e[0m\n", -1);
	here_doc = !ft_strncmp(argv[1], "here_doc", 9);
	if (here_doc && argc < 6)
		error_msg("\e[0;31mError\nUsage: ./pipex here_doc limiter cmd1 "
			"cmd2 outfile\e[0m\n", -1);
	childs = argc - 3;
	pids = create_child_prcs(childs, argv, here_doc);
	status = child_wait_pid(pids, childs);
	free(pids);
	exit(status);
}
