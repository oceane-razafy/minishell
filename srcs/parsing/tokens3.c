/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:19:56 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 20:46:57 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tk_merge_quote(t_token **head, t_token *token1, t_token *token2)
{
	t_token	*new;
	char	*new_content;

	new_content = ft_strjoin(token1->content, token2->content);
	if (!new_content)
		return (0);
	new = tk_new(new_content);
	if (token1->delim_quote || token2->delim_quote)
		new->delim_quote = 1;
	if (!new)
		return (0);
	new->prev = token1->prev;
	new->next = token2->next;
	if (new->prev)
		new->prev->next = new;
	else
		*head = new;
	if (new->next)
		new->next->prev = new;
	if (token2->join_next)
		new->join_next = 1;
	tk_delone(token1);
	tk_delone(token2);
	return (new);
}

t_token	*tk_merge(t_token **head, t_token *token1, t_token *token2)
{
	t_token	*new;
	char	*new_content;
	char	*tmp;

	tmp = ft_strjoin(token1->content, " ");
	if (!tmp)
		return (0);
	new_content = ft_strjoin(tmp, token2->content);
	if (!new_content)
		return (0);
	free (tmp);
	new = tk_new(new_content);
	if (!new)
		return (0);
	new->prev = token1->prev;
	new->next = token2->next;
	if (new->prev)
		new->prev->next = new;
	else
		*head = new;
	if (new->next)
		new->next->prev = new;
	tk_delone(token1);
	tk_delone(token2);
	return (new);
}
