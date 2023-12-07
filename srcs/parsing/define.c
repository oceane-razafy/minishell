/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:06:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/18 16:57:48 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_redirs(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (ft_isinbase(browse->content[0], "<|>") && !browse->quote)
			browse->type = 'R';
		browse = browse->next;
	}
	return (1);
}

int	define_delims(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	if (!browse)
		return (0);
	while (browse->next)
	{
		if (!ft_strncmp(browse->content, "<<", 2) && !browse->next->type)
			browse->next->type = 'D';
		browse = browse->next;
	}
	return (1);
}

int	define_files(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	if (!browse)
		return (0);
	while (browse->next)
		browse = browse->next;
	while (browse->prev)
	{
		if (browse->prev->content[0] == '>'
			&& browse->prev->type == 'R' && browse->type != 'R')
			browse->type = 'F';
		else if (browse->prev->content[0] == '<'
			&& !browse->prev->content[1] && browse->prev->type == 'R'
			&& browse->type != 'R')
		{
			browse->type = 'F';
		}
		browse = browse->prev;
	}
	return (1);
}
