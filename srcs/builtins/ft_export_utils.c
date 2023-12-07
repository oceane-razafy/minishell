/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:23:19 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/18 17:18:51 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_identifier(char **argv, int *j, int i)
{
	if (ft_isalnum(argv[*j][i]) == 0 && (argv[*j][i] != '_'))
	{
		ft_error_identifier("export", argv[*j]);
		(*j)++;
		return (-1);
	}
	return (0);
}

void	ft_print_export(char *str)
{
	while (*str != '=')
		printf("%c", *(str++));
	printf("%c\"", *str);
	str++;
	while (*str)
		printf("%c", *(str++));
	printf("\"\n");
}

void	ft_get_env_min(char **min, int *pos_min, int size, char **env)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			*min = env[i];
			*pos_min = i;
			break ;
		}
		i++;
	}
}

int	ft_print_env_min(char **env, int size)
{
	int		i;
	char	*min;
	int		pos_min;

	ft_get_env_min(&min, &pos_min, size, env);
	i = 0;
	while (i < size)
	{
		if (env[i] == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strcmp_env(env[i], min) < 0)
		{
			min = env[i];
			pos_min = i;
		}	
		i++;
	}
	printf("declare -x ");
	ft_print_export(min);
	return (pos_min);
}

int	ft_check_is_first_digit(char **argv, int *j, char *cmd)
{
	if (ft_isdigit(argv[*j][0]) == 1)
	{
		if (ft_strcmp(cmd, "export") == 0)
			ft_error_identifier(cmd, argv[*j]);
		(*j)++;
		return (-1);
	}
	return (0);
}
