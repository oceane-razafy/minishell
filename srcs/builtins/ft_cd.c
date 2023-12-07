/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:00:07 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_without_arg(t_minishell *mini)
{
	char	*new_path;
	int		i;

	i = 0;
	while (mini->data_env.envp[i])
	{
		if (ft_strcmp_env("HOME=", mini->data_env.envp[i]) == 0)
			break ;
		i++;
	}
	if (mini->data_env.envp[i] != NULL)
		new_path = mini->data_env.envp[i] + 5;
	else
	{
		write(2, "cd: HOME not set\n", 17);
		ft_exit_utils(1, 1, mini);
		return (-1);
	}
	if (chdir(new_path) != 0)
	{
		perror("cd: chdir");
		ft_exit_utils(1, 1, mini);
		return (-1);
	}
	return (0);
}

void	ft_cd_too_many_args(t_minishell *mini)
{
	write(2, "cd: too many arguments\n", 23);
	ft_exit_utils(1, 1, mini);
}

int	ft_go_to_dir(t_minishell *mini)
{
	if (mini->cmd.argc == 1)
	{
		if (ft_cd_without_arg(mini) == -1)
			return (-1);
	}
	else
	{
		if (chdir(mini->cmd.argv[1]) != 0)
		{
			perror("cd: chdir");
			ft_exit_utils(1, 1, mini);
			return (-1);
		}
	}
	return (0);
}

void	ft_change_all_pwd(char *pwd, t_minishell *mini)
{
	ft_change_g_pwd(pwd, mini);
	ft_update_pwd(pwd, &mini->data_env);
}

void	ft_cd(t_minishell *mini)
{
	char	*pwd;

	if (mini->cmd.argc > 2)
	{
		ft_cd_too_many_args(mini);
		return ;
	}
	if (mini->cmd.argc > 1)
	{
		if (access(mini->cmd.argv[1], F_OK) == -1)
		{
			perror("cd");
			ft_exit_utils(1, 1, mini);
			return ;
		}	
	}
	if (ft_update_oldpwd(mini) == -1)
		return (ft_exit_utils(1, 1, mini));
	if (ft_go_to_dir(mini) == -1)
		return ;
	pwd = ft_get_pwd(mini);
	if (pwd == NULL)
		ft_error(200, mini);
	ft_change_all_pwd(pwd, mini);
	ft_exit_utils(EXIT_SUCCESS, 1, mini);
}
