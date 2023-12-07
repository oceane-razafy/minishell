/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:58 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:18:57 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_oldpwd_utils(t_minishell *mini, char *oldpwd)
{
	int	i;

	i = 0;
	while (mini->data_env.envp[i])
	{
		if (ft_strcmp_env("OLDPWD=", mini->data_env.envp[i]) == 0)
			break ;
		i++;
	}
	if (mini->data_env.envp[i] != NULL)
	{
		free(mini->data_env.envp[i]);
		mini->data_env.envp[i] = oldpwd;
	}
	else
	{
		if (mini->data_env.oldpwd_done != 1)
		{
			mini->data_env.envp = ft_add_var_env(&mini->data_env, oldpwd);
			free(oldpwd);
			if (mini->data_env.envp == NULL)
				ft_error(200, mini);
		}
		mini->data_env.oldpwd_done = 1;
	}
}

int	ft_update_oldpwd(t_minishell *mini)
{
	char	current_path[1000];
	char	*oldpwd;
	char	*pwd;

	if (mini->data_env.pwd != NULL)
		pwd = mini->data_env.pwd;
	else
		pwd = ft_get_pwd_env(mini->data_env.envp);
	if (pwd == NULL)
	{
		if (getcwd(current_path, sizeof(current_path)) == NULL)
			return (perror("cd: getcwd"), -1);
		oldpwd = ft_strjoin("OLDPWD=", current_path);
		if (oldpwd == NULL)
			ft_error(200, mini);
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd);
		if (oldpwd == NULL)
			ft_error(200, mini);
	}
	ft_update_oldpwd_utils(mini, oldpwd);
	return (0);
}

void	ft_update_pwd(char *pwd, t_data_env *s_data_env)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env("PWD=", s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] != NULL)
	{
		free(s_data_env->envp[i]);
		s_data_env->envp[i] = pwd;
	}
	else
		free(pwd);
}

char	*ft_get_pwd(t_minishell *mini)
{
	char	*pwd;
	char	current_path[1000];
	char	*pwd_env;
	char	*pwd_slash;

	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("cd: getcwd");
		if (mini->data_env.pwd != NULL)
			pwd_env = ft_strjoin("PWD=", mini->data_env.pwd);
		else
			pwd_env = ft_strjoin("PWD=", ft_get_pwd_env(mini->data_env.envp));
		if (pwd_env == NULL)
			ft_error(200, mini);
		pwd_slash = ft_strjoin(pwd_env, "/");
		if (pwd_slash == NULL)
			return (free(pwd_env), NULL);
		free(pwd_env);
		pwd = ft_strjoin(pwd_slash, mini->cmd.argv[1]);
		free(pwd_slash);
	}
	else
		pwd = ft_strjoin("PWD=", current_path);
	return (pwd);
}

void	ft_change_g_pwd(char *pwd, t_minishell *mini)
{
	free(mini->data_env.pwd);
	mini->data_env.pwd = ft_strdup(pwd + 4);
	if (mini->data_env.pwd == NULL)
		ft_error(200, mini);
}
