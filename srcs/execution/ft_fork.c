/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:34:54 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/17 15:11:19 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
		ft_error(1, mini);
	else if (cmd->pid == 0)
	{
		if (signal(SIGQUIT, ft_sigquit) == SIG_ERR)
			ft_exit_exec(1, mini);
		ft_all_redir(mini);
		if (cmd->has_cmd == 0 && cmd->first_arg != NULL)
			ft_error_cmd_not_found(mini);
		if (cmd->has_cmd == 0 && cmd->first_arg == NULL)
			ft_exit_exec(0, mini);
		ft_close_all_fds(mini);
		ft_exe_builtin2(mini);
		ft_exec_not_builtin(mini);
	}
	else
		ft_after_fork_parent(cmd);
}

void	ft_get_cmd_path(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (!access(cmd->argv[0], X_OK))
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
	else
	{
		if (ft_strcmp(".", cmd->argv[0]) == 0)
			ft_filename_required(mini);
		cmd->cmd_path = find_cmd_path(cmd->argv[0], mini->data_env.envp);
	}
	if (cmd->cmd_path == NULL)
		ft_error(200, mini);
}

void	ft_exec_not_builtin(t_minishell *mini)
{
	struct stat		f_stat;
	t_cmd			*cmd;

	cmd = &mini->cmd;
	ft_get_cmd_path(mini);
	close(mini->data_env.stdin);
	close(mini->data_env.stdout);
	if (stat(cmd->cmd_path, &f_stat) == -1)
	{
		perror("");
		ft_exit_exec(1, mini);
	}
	if (ft_srch('/', cmd->cmd_path) != -1 && S_ISDIR(f_stat.st_mode))
	{
		write(2, cmd->cmd_path, ft_strlen(cmd->cmd_path));
		write(2, ": Is a directory\n", 17);
		ft_exit_exec(126, mini);
	}
	if (ft_srch('/', cmd->cmd_path) == -1)
		ft_error_cmd_not_found2(mini);
	execve(cmd->cmd_path, cmd->argv, mini->data_env.envp);
	if (errno == ENOEXEC)
		ft_exit_exec(0, mini);
	ft_error(1, mini);
}

void	ft_after_fork_parent(t_cmd *cmd)
{
	if (cmd->old_pipefd[0] != -2 && cmd->old_pipefd[1] != -2)
	{
		ft_close(&cmd->old_pipefd[0]);
		ft_close(&cmd->old_pipefd[1]);
	}
	cmd->old_pipefd[0] = cmd->pipefd[0];
	cmd->old_pipefd[1] = cmd->pipefd[1];
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
		ft_close(&cmd->fd_in);
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
}

void	ft_exe_builtin2(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("echo", cmd->argv[0]) == 0)
			ft_echo(mini);
		else if (ft_strcmp("cd", cmd->argv[0]) == 0)
			ft_cd(mini);
		else if (ft_strcmp("pwd", cmd->argv[0]) == 0)
			ft_pwd(mini);
		else if (ft_strcmp("export", cmd->argv[0]) == 0)
			ft_export(mini);
		else if (ft_strcmp("unset", cmd->argv[0]) == 0)
			ft_unset(mini);
		else if (ft_strcmp("env", cmd->argv[0]) == 0)
			ft_env(mini);
		else if (ft_strcmp("exit", cmd->argv[0]) == 0)
			ft_exit(mini);
	}
}
