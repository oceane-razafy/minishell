/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 16:01:38 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_minishell_g *g_mini, t_minishell *mini)
{
	int		builtin_done;
	int		pipe_before;
	t_token	*head;

	head = mini->ltable.tklist_head;
	builtin_done = 0;
	pipe_before = 0;
	ft_before_launch_pipeline(mini);
	while (1)
	{
		ft_init_cmd(&mini->cmd);
		fetch_heredoc(&mini->cmd, head,
			&mini->data_env, mini);
		if (g_mini->inside_heredoc == -1)
			break ;
		head = ft_get_cmd(head, mini, pipe_before);
		ft_execute_cmd(mini, builtin_done);
		if (mini->cmd.final_cmd == 1)
			break ;
		ft_prepare_before_next_cmd(mini, &pipe_before, &builtin_done);
	}
	ft_waitpid(mini);
	ft_restore_before_next_prompt(mini);
}

void	ft_execute_cmd(t_minishell *mini, int builtin_done)
{
	if (pipe(mini->cmd.pipefd) == -1)
		ft_error(1, mini);
	if (mini->cmd.inside_pipe == 0)
			builtin_done = ft_exe_builtin1(mini);
	if (builtin_done == 0)
		ft_fork(mini);
}

void	ft_prepare_before_next_cmd(
			t_minishell *mini, int *pipe_before, int *builtin_done)
{
	*pipe_before = ft_init_pipe_before(&mini->cmd);
	ft_free_cmd(&mini->cmd);
	*builtin_done = 0;
}

void	ft_waitpid(t_minishell *mini)
{
	int	res;
	int	status;

	res = 0;
	status = 0;
	while (res != -1 || errno != ECHILD)
	{
		res = waitpid(-1, &status, 0);
		if (res == mini->cmd.final_pid)
			ft_get_status(status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 200)
				ft_error(200, mini);
		}
		if (res == -1 && (errno != EINTR && errno != ECHILD))
			ft_error(1, mini);
	}
}

int	ft_exe_builtin1(t_minishell *mini)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("cd", cmd->argv[0]) == 0)
			return (ft_cd(mini), 1);
		else if (ft_strcmp("export", cmd->argv[0]) == 0 && cmd->argc > 1)
			return (ft_export(mini), 1);
		else if (ft_strcmp("unset", cmd->argv[0]) == 0)
			return (ft_unset(mini), 1);
		else if (ft_strcmp("exit", cmd->argv[0]) == 0)
			return (ft_exit(mini), 1);
	}
	return (0);
}
