/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:17:00 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 15:25:41 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_option(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	if (*str == 0)
		return (0);
	while (*str)
	{
		if (*str != 'n')
			break ;
		str++;
	}
	if (*str != 0)
		return (0);
	return (1);
}

int	ft_compute_start_arg(int has_option)
{
	if (has_option == 1)
		return (2);
	else
		return (1);
}

void	ft_echo(t_minishell *mini)
{
	int	i;
	int	has_option;

	has_option = 0;
	if (mini->cmd.argc == 1)
	{
		write(1, "\n", 1);
		return (ft_exit_utils(EXIT_SUCCESS, 1, mini));
	}
	has_option = ft_check_option(mini->cmd.argv[1]);
	if ((mini->cmd.argc == 2) && (has_option == 1))
		return (ft_exit_utils(EXIT_SUCCESS, 1, mini));
	i = ft_compute_start_arg(has_option);
	while (i < mini->cmd.argc && ft_check_option(mini->cmd.argv[i]))
		i++;
	while (i < mini->cmd.argc)
	{
		write(1, mini->cmd.argv[i], ft_strlen(mini->cmd.argv[i]));
		if (i++ != mini->cmd.argc - 1)
			write(1, " ", 1);
	}
	if (has_option != 1)
		write(1, "\n", 1);
	ft_exit_utils(EXIT_SUCCESS, 1, mini);
}
