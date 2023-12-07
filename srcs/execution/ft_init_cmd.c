/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:31:47 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 00:59:49 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->pipe = 0;
	cmd->pipefd[0] = -2;
	cmd->pipefd[1] = -2;
	cmd->final_cmd = 0;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->cmd_path = NULL;
	cmd->final_pid = 0;
	cmd->has_cmd = 0;
	cmd->first_arg = NULL;
	cmd->first_arg_done = 0;
	cmd->fd_heredoc = -2;
	cmd->inside_pipe = 0;
	cmd->error_fd = NULL;
	cmd->filename = NULL;
}
