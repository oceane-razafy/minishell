/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:08:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 01:03:52 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var_format_export(char **argv, int *j)
{
	int	i;

	if (ft_check_is_first_digit(argv, j, "export") == -1)
		return (-1);
	if (ft_srch('=', argv[*j]) < 1)
	{
		if (ft_srch('=', argv[*j]) == 0)
		{
			ft_error_identifier("export", argv[*j]);
			(*j)++;
			return (-1);
		}
		i = 0;
		while (argv[*j][i])
		{
			if (ft_check_identifier(argv, j, i) == -1)
				return (-1);
			i++;
		}
	}
	return (ft_last_check_format_export(argv, j));
}

int	ft_last_check_format_export(char **argv, int *j)
{
	int	i;

	i = 0;
	while (argv[*j][i])
	{
		if (argv[*j][i] == '=')
			break ;
		if (ft_check_identifier(argv, j, i) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	ft_export_without_arg(t_minishell *mini)
{
	int		i;
	char	**dup_env;
	int		min;

	dup_env = ft_strdup_env(mini->data_env.envp, 1, mini);
	if (dup_env == NULL)
		ft_error(200, mini);
	i = 0;
	while (i < mini->data_env.size)
	{
		min = ft_print_env_min(dup_env, mini->data_env.size);
		free(dup_env[min]);
		dup_env[min] = NULL;
		i++;
	}
	free(dup_env[i]);
	free(dup_env);
}

void	ft_export_with_arguments(t_minishell *mini, int j)
{
	int			i;
	t_data_env	*data_env;

	data_env = &mini->data_env;
	i = 0;
	while (data_env->envp[i])
	{
		if (ft_strcmp_env(mini->cmd.argv[j], data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (data_env->envp[i] == NULL)
	{
		data_env->envp = ft_add_var_env(data_env, mini->cmd.argv[j]);
		if (data_env->envp == NULL)
			ft_error(200, mini);
	}	
	else
	{
		free(data_env->envp[i]);
		data_env->envp[i] = NULL;
		data_env->envp[i] = ft_strdup(mini->cmd.argv[j]);
		if (data_env->envp[i] == NULL)
			ft_error(200, mini);
	}
}

void	ft_export(t_minishell *mini)
{
	int	j;
	int	status;

	status = 0;
	if (mini->cmd.argc == 1)
	{
		ft_export_without_arg(mini);
		return (ft_exit_utils(EXIT_SUCCESS, 1, mini));
	}
	j = 1;
	while (j < mini->cmd.argc)
	{
		if ((ft_check_var_format_export(mini->cmd.argv, &j) == -1)
			|| (ft_check_empty_var(mini->cmd.argv, &j, "export") == -1))
		{
			status = 1;
			continue ;
		}
		if (ft_srch('=', mini->cmd.argv[j]) >= 1)
			ft_export_with_arguments(mini, j);
		j++;
	}
	ft_exit_utils(status, 1, mini);
}
