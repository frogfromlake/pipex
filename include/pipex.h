/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fquist <fquist@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:49:49 by fquist            #+#    #+#             */
/*   Updated: 2022/01/31 17:17:29 by fquist           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
/* STANDARD INCLUDES														  */
/* ************************************************************************** */
# include <stdbool.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"

/* ************************************************************************** */
/* CHILDS																	  */
/* ************************************************************************** */
pid_t	*create_child_prcs(int childs, char **argv, bool here_doc);
void	child_prc(int childs, int i, int **pipes, char **argv);
int		child_prc_exec(int pipe_read, int pipe_write, char *str_cmd);

/* ************************************************************************** */
/* PIPES																	  */
/* ************************************************************************** */
int		**create_pipes_arr(int n);
int		close_pipes(int **pipes, int childs, int child_nbr);
void	free_pipes_arr(int **arr, int elements);

/* ************************************************************************** */
/* COMMANDS																	  */
/* ************************************************************************** */
char	**get_commands(const char *cmd_str, int *code);
int		set_cmd_path(char **cmd);

/* ************************************************************************** */
/* UTILS																	  */
/* ************************************************************************** */
int		open_file(char *file, int mod, int rights);
int		error_msg(char *error_msg, int r_value);
int		file_error(char *before, char *message, char *after);
int		child_wait_pid(pid_t *pid, int n);

#endif
