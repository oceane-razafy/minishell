/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:10:58 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 17:38:35 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_remove_var_in_env(int i, t_data_env *s_data_env)
{
	char	**envp;

	envp = s_data_env->envp;
	while (1)
	{
		free(envp[i]);
		if (envp[i + 1] != NULL)
		{
			envp[i] = ft_strdup(envp[i + 1]);
			if (envp[i] == NULL)
				return (-1);
		}
		else
			envp[i] = NULL;
		if (envp[i] == NULL)
			break ;
		i++;
	}
	s_data_env->size--;
	return (0);
}

char	**ft_add_var_env(t_data_env *s_data_env, char *new_var)
{
	char	**dup_env;
	int		i;

	i = 0;
	dup_env = (char **)malloc(sizeof(char *) * (s_data_env->size + 2));
	if (dup_env == NULL)
		return (NULL);
	while (s_data_env->envp[i])
	{
		dup_env[i] = ft_strdup(s_data_env->envp[i]);
		if (dup_env[i] == NULL)
			return (ft_free_env(dup_env, i), NULL);
		free(s_data_env->envp[i]);
		i++;
	}
	free(s_data_env->envp[i]);
	free(s_data_env->envp);
	dup_env[i++] = ft_strdup(new_var);
	if (dup_env[i - 1] == NULL)
		return (ft_free_env(dup_env, i - 1), NULL);
	dup_env[i] = NULL;
	s_data_env->size++;
	return (dup_env);
}

void	ft_free_env(char **env, int size)
{
	int	i;

	i = 0;
	if (env == NULL)
		return ;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			free(env[i]);
			env[i] = NULL;
		}
		i++;
	}
	free(env);
}
