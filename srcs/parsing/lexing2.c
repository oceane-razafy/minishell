/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 07:12:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/29 08:07:05 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_joins(t_lexing *ltable, t_token *quoted,
	int reader, int quote_len)
{
	if (ltable->input[reader + quote_len] && ltable->input[reader + quote_len]
		!= ' ' && ltable->input[reader + quote_len] != '\t')
			quoted->join_next = 1;
	if (!reader)
		return ;
	else if (ltable->input [reader - 1] != ' '
		&& ltable->input[reader - 1] != '\t')
		quoted->join_prev = 1;
}
