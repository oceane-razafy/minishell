/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:08:02 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/17 20:00:47 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_all_redir(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (cmd->old_pipefd[0] != -2
		&& cmd->old_pipefd[1] != -2 && cmd->fd_in == -2)
	{
		ft_close(&cmd->old_pipefd[1]);
		if (dup2(cmd->old_pipefd[0], STDIN_FILENO) == -1)
			ft_error(1, mini);
		ft_close(&cmd->old_pipefd[0]);
	}
	ft_redir_files(mini);
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		ft_close(&cmd->pipefd[0]);
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			ft_error(200, mini);
		ft_close(&cmd->pipefd[1]);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
	ft_error_redirections(mini);
}

void	ft_redir_files(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error(200, mini);
		ft_close(&cmd->fd_in);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error(200, mini);
	}
}

void	ft_error_redirections(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (cmd->fd_out == -1 || cmd->fd_in == -1)
	{
		if (cmd->filename != NULL)
		{
			write(2, cmd->filename, ft_strlen(cmd->filename));
			write(2, ": ", 2);
		}
		write(2, cmd->error_fd, ft_strlen(cmd->error_fd));
		write(2, "\n", 1);
		ft_exit_exec(1, mini);
	}
}
