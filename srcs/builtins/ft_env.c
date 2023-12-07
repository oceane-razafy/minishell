/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:06:31 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:05:37 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *mini)
{
	int	i;

	if (mini->cmd.argc > 1)
		ft_exit_utils(EXIT_SUCCESS, 1, mini);
	else
	{
		i = 0;
		while (mini->data_env.envp[i])
			printf("%s\n", mini->data_env.envp[i++]);
		ft_exit_utils(EXIT_SUCCESS, 1, mini);
	}
}
