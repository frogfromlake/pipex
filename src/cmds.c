/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:50:10 by fquist            #+#    #+#             */
/*   Updated: 2022/01/31 17:16:07 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_env_path(void);
static void	append_slash(char **cmd_paths);

char	**get_commands(const char *cmd_str, int *code)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd_str, ' ');
	if (cmd_args == NULL)
	{
		*code = ENOMEM;
		return (NULL);
	}
	*code = set_cmd_path(&cmd_args[0]);
	if (*code != 0)
	{
		file_error("pipex", "command not found", cmd_args[0]);
		ft_free_split(cmd_args);
		return (NULL);
	}
	return (cmd_args);
}

int	set_cmd_path(char **cmd)
{
	int		i;
	char	*tmp;
	char	**cmd_paths;

	i = 0;
	if (access(*cmd, F_OK) == 0)
		return (0);
	cmd_paths = get_env_path();
	if (cmd_paths == NULL)
		return (ENOMEM);
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], *cmd);
		if (access(tmp, F_OK) == 0)
		{
			free(*cmd);
			*cmd = tmp;
			ft_free_split(cmd_paths);
			return (0);
		}
		free(tmp);
		i++;
	}
	ft_free_split(cmd_paths);
	return (127);
}

static char	**get_env_path(void)
{
	int			i;
	char		**cmd_paths;
	extern char	**environ;

	i = 0;
	if (environ == NULL)
		return (NULL);
	cmd_paths = NULL;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			cmd_paths = ft_split((environ[i] + 5), ':');
			if (cmd_paths == NULL)
				return (NULL);
			append_slash(cmd_paths);
			break ;
		}
		i++;
	}
	return (cmd_paths);
}

static void	append_slash(char **cmd_paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd_paths[i])
	{
		if (cmd_paths[i][ft_strlen(cmd_paths[i]) - 1] != '/')
		{
			tmp = cmd_paths[i];
			cmd_paths[i] = ft_strjoin(cmd_paths[i], "/");
			free(tmp);
			tmp = NULL;
		}
		i++;
	}
}
