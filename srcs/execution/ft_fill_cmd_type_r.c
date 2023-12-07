/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_type_r.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:46:28 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/17 20:23:42 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd_for_type_r(t_minishell *mini, t_token *lst)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (lst->content[0] == '<')
	{
		if (cmd->fd_in == -1)
			return ;
		if (cmd->fd_in != -2)
			close(cmd->fd_in);
		if (lst->content[1] == '<')
		{
			cmd->fd_in = open("/tmp/.hdoc.txt", O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				ft_error(1, mini);
		}
		else
			ft_fill_cmd_for_type_r2(cmd, lst);
	}
	ft_fill_cmd_for_type_r3(&mini->cmd, lst);
}

void	ft_fill_cmd_for_type_r2(t_cmd *cmd, t_token *lst)
{
	if (lst->next == NULL)
		ft_ambiguous_redir(cmd, lst);
	else
	{
		cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
		if (cmd->fd_in == -1)
		{
			cmd->fd_out = -1;
			cmd->error_fd = strerror(errno);
			cmd->filename = lst->next->content;
		}
	}
}

int	ft_ambiguous_redir(t_cmd *cmd, t_token *lst)
{
	if (lst->next == NULL || (lst->next != NULL && lst->next->type == 'R'))
	{
		cmd->fd_in = -1;
		cmd->fd_out = -1;
		cmd->error_fd = "ambiguous redirect";
		cmd->filename = NULL;
		return (1);
	}
	return (0);
}

void	ft_fill_cmd_for_type_r3(t_cmd *cmd, t_token *lst)
{
	char	*outfile;

	if (lst->next != NULL)
		outfile = lst->next->content;
	if (lst->content[0] == '>')
	{
		if (cmd->fd_out == -1)
			return ;
		if (cmd->fd_out != -2)
			close(cmd->fd_out);
		if (ft_ambiguous_redir(cmd, lst) == 1)
			return ;
		if (lst->content[1] == '>')
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0664);
		else
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (cmd->fd_out == -1)
		{
				cmd->fd_in = -1;
				cmd->error_fd = strerror(errno);
				cmd->filename = lst->next->content;
		}
	}
}
