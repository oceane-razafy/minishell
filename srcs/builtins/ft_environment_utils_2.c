/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:56:46 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 19:16:06 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_env(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == 0 && s2[i] == '=')
		return (0);
	if (s1[i] == '=' && s2[i] == 0)
		return (0);
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s2[i] == '=' && s1[i] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_compute_env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	ft_check_has_oldpwd(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp_env("OLDPWD=", envp[i]) == 0)
			break ;
		i++;
	}
	if (envp[i] != NULL)
		return (1);
	else
		return (0);
}

char	**ft_strdup_env_2(char **envp, char **env, int size, int take_oldpwd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		if ((ft_strcmp_env("OLDPWD=", envp[i]) == 0) && take_oldpwd == 0)
		{
			i++;
			continue ;
		}
		env[j++] = ft_strdup(envp[i]);
		if (env[j - 1] == NULL)
		{
			ft_free_env(env, j - 1);
			return (NULL);
		}
		i++;
	}
	env[size] = NULL;
	return (env);
}

char	**ft_strdup_env(char **envp, int take_oldpwd, t_minishell *mini)
{
	int		size;
	char	**env;
	int		has_oldpwd;

	size = ft_compute_env_len(envp);
	has_oldpwd = ft_check_has_oldpwd(envp);
	if (has_oldpwd == 1 && take_oldpwd == 0)
	{
		size--;
		mini->data_env.size--;
	}
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	return (ft_strdup_env_2(envp, env, size, take_oldpwd));
}
