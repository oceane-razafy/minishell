/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:39:59 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:40:11 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc(t_lexing *ltable, t_data_env *data_env,
			char *error_msg)
{
	tk_clear(&ltable->tklist_head);
	ft_free_env(data_env->envp, data_env->size);
	free(data_env->pwd);
	ft_putstr_fd(error_msg, 2);
	exit(g_mini.exit_status);
}
