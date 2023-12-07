/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:33:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 18:26:12 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->argv != NULL)
		free_array(cmd->argv);
	if (cmd->cmd_path != NULL)
		free(cmd->cmd_path);
	if (cmd->first_arg != NULL)
		free(cmd->first_arg);
	cmd->argv = NULL;
	cmd->cmd_path = NULL;
	cmd->first_arg = NULL;
}
