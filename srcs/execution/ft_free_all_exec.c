/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:33:38 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:47:01 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all_exec(t_minishell *mini)
{
	ft_close_all_fds(mini);
	ft_free_cmd(&mini->cmd);
	ft_free_env(mini->data_env.envp, mini->data_env.size);
	tk_clear(&mini->ltable.tklist_head);
	free(mini->ltable.input);
	free(mini->data_env.pwd);
	rl_clear_history();
}
