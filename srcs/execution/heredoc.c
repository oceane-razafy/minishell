/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:15:24 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 17:25:17 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unlink(t_cmd *cmd)
{
	if (cmd->fd_heredoc != -2)
		cmd->fd_heredoc = -2;
	if (!access("/tmp/.hdoc.txt", F_OK))
		unlink("/tmp/.hdoc.txt");
}

char	*process_line(char *line, t_token *delim, t_data_env *data_env)
{
	char	*new_line;

	if (delim->delim_quote || !ft_isinbase('$', line)
		|| ft_isinbase(line[0], "\'"))
		return (line);
	else if (!ft_strncmp(line, delim->content, delim_len(delim->content, line)))
		return (line);
	new_line = expand_process(line, data_env);
	if (!new_line)
		return (0);
	return (new_line);
}

void	heredoc_process(t_cmd *cmd, t_data_env *data_env,
			t_token *delim, t_minishell *mini)
{
	char	*line;
	char	*new_line;

	while (g_mini.inside_heredoc)
	{
		write(1, "heredoc> ", 9);
		line = gnl();
		if (!line)
			return (free_heredoc(&mini->ltable, data_env,
					"cannot allocate memory\n"));
		if (*line == 0)
		{
			write(1, "\n", 1);
			return (free(line));
		}
		new_line = process_line(line, delim, data_env);
		if (!new_line)
			return (free_heredoc(&mini->ltable, data_env,
					"cannot allocate memory\n"));
		if (ft_strncmp(delim->content,
				new_line, delim_len(delim->content, new_line)) == 0)
			return (free(new_line));
		write(cmd->fd_heredoc, new_line, ft_strlen(new_line));
		free (new_line);
	}
}

void	fetch_heredoc(t_cmd *cmd, t_token *tklist_head,
			t_data_env *data_env, t_minishell *mini)
{
	t_token	*delim;
	t_token	*browse;
	int		status;

	browse = tklist_head;
	ft_unlink(cmd);
	delim = fetch_delim(&browse);
	if (!delim)
		return ;
	waitpid(cmd->pid, &status, 0);
	g_mini.inside_heredoc = 1;
	while (g_mini.inside_heredoc == 1 && delim)
	{
		cmd->fd_heredoc = open("/tmp/.hdoc.txt", O_CREAT | O_WRONLY, 0664);
		if (cmd->fd_heredoc < 0)
			return (free_heredoc(&mini->ltable, data_env,
					"Permission denied\n"), set_error(13));
		heredoc_process(cmd, data_env, delim, mini);
		if (browse && browse->content[0] != '|')
		{
			browse = browse->next;
			delim = fetch_delim(&browse);
		}
		ft_close (&cmd->fd_heredoc);
	}
}
