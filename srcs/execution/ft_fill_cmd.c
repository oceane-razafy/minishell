/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:10:45 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 16:48:39 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd(t_minishell *mini, t_token *lst)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	if (lst->type == 'R')
		ft_fill_cmd_for_type_r(mini, lst);
	if (lst->type == 'C')
	{
		ft_fill_argc_argv(mini, lst);
		cmd->has_cmd = 1;
	}
	if (lst->type == 'A')
	{
		if (cmd->first_arg_done != 1)
			cmd->first_arg = ft_strdup(lst->content);
		if (cmd->first_arg == NULL)
			ft_error(1, mini);
		cmd->first_arg_done = 1;
	}
}

void	ft_fill_argc_argv(t_minishell *mini, t_token *lst)
{
	t_cmd	*cmd;

	cmd = &mini->cmd;
	ft_malloc_argv(mini, lst);
	ft_split_cmd_option(mini, lst);
	if (lst->next == NULL)
		return ;
	lst = lst->next;
	while (lst != NULL)
	{
		if (lst->content[0] == '|' && lst->type == 'R')
			break ;
		if (lst->type == 'A')
			cmd->argv[cmd->argc++] = ft_strdup(lst->content);
		if (cmd->argv[cmd->argc - 1] == NULL)
			ft_error(1, mini);
		lst = lst->next;
	}
}

void	ft_split_cmd_option(t_minishell *mini, t_token *lst)
{
	int		space_pos;
	int		len_option;
	char	*content;
	t_cmd	*cmd;

	cmd = &mini->cmd;
	content = lst->content;
	space_pos = ft_srch(' ', content);
	len_option = ft_strlen(content + space_pos + 1);
	if (space_pos != -1)
	{
		cmd->argv[cmd->argc++] = ft_substr(content, 0, space_pos);
		cmd->argv[cmd->argc++] = ft_substr(content, space_pos + 1, len_option);
		if (cmd->argv[cmd->argc - 1] == NULL
			|| cmd->argv[cmd->argc - 2] == NULL)
			ft_error(1, mini);
	}
	else
		cmd->argv[cmd->argc++] = ft_strdup(content);
	if (cmd->argv[cmd->argc - 1] == NULL)
		ft_error(1, mini);
}

void	ft_malloc_argv(t_minishell *mini, t_token *lst)
{
	int		argc;
	t_cmd	*cmd;

	cmd = &mini->cmd;
	argc = 1;
	if (ft_srch(' ', lst->content) != -1)
		argc++;
	while (lst != NULL)
	{
		if (lst->content[0] == '|' && lst->type == 'R')
			break ;
		if (lst->type == 'A')
			argc++;
		lst = lst->next;
	}
	cmd->argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (cmd->argv == NULL)
		ft_error(1, mini);
	cmd->argv[argc] = NULL;
}
