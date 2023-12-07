/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:05:57 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 17:18:11 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_var_format_unset(char **argv, int *j)
{
	int	is_broken;
	int	i;

	is_broken = 0;
	i = 0;
	if (ft_check_is_first_digit(argv, j, "unset") == -1)
		return (-1);
	while (argv[*j][i])
	{
		if (ft_isalnum(argv[*j][i]) == 0 && (argv[*j][i] != '_'))
		{
			is_broken = 1;
			break ;
		}
		i++;
	}
	if (is_broken == 1)
	{
		(*j)++;
		return (-1);
	}
	return (0);
}

int	ft_unset_with_arg(char **argv, t_data_env *s_data_env, int j)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env(argv[j], s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] == NULL)
		return (0);
	return (ft_remove_var_in_env(i, s_data_env));
}

void	ft_unset(t_minishell *mini)
{
	int	j;
	int	status;

	status = 0;
	j = 1;
	while (j < mini->cmd.argc)
	{
		if (ft_check_var_format_unset(mini->cmd.argv, &j) == -1
			|| (ft_check_empty_var(mini->cmd.argv, &j, "unset") == -1))
		{
			continue ;
		}	
		if (ft_unset_with_arg(mini->cmd.argv, &mini->data_env, j) == -1)
			ft_error(200, mini);
		j++;
	}
	ft_exit_utils(status, 1, mini);
}
