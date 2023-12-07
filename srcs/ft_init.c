/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:18:39 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 19:15:50 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data_env(t_data_env *s_data_env, char **envp, t_minishell *mini)
{
	s_data_env->size = ft_compute_env_len(envp);
	s_data_env->envp = ft_strdup_env(envp, 0, mini);
	if (s_data_env->envp == NULL)
	{
		perror("");
		ft_free_env(s_data_env->envp, s_data_env->size);
		exit(EXIT_FAILURE);
	}
	s_data_env->stdin = -2;
	s_data_env->stdout = -2;
}

char	*ft_init_pwd(char **envp)
{
	char	current_path[1000];
	char	*cwd;
	char	*pwd;

	pwd = ft_get_pwd_env(envp);
	if (pwd == NULL)
	{
		cwd = getcwd(current_path, sizeof(current_path));
		if (cwd == NULL)
		{
			perror("getcwd:");
			exit (EXIT_FAILURE);
		}
		else
			return (cwd);
	}
	else
		return (pwd);
}

void	ft_init_mini(t_minishell_g *g_mini, t_minishell *mini, char **envp)
{
	g_mini->exit_status = 0;
	g_mini->status_done = 0;
	g_mini->inside_heredoc = 0;
	mini->data_env.oldpwd_done = 0;
	mini->data_env.pwd = NULL;
	mini->data_env.pwd = ft_strdup(ft_init_pwd(envp));
	if (mini->data_env.pwd == NULL)
		exit (EXIT_FAILURE);
	ft_init_data_env(&mini->data_env, envp, mini);
	init_table(&mini->ltable);
}

void	init_table(t_lexing *ltable)
{
	ltable->tklist_head = 0;
	ltable->input = 0;
	ltable->tklist_size = 0;
}
