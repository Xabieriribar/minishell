/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:34:13 by rick              #+#    #+#             */
/*   Updated: 2026/01/25 12:34:53 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_word_append(t_token *last, char *str)
{
	int		i;
	char	*buff;
	char	*new;

	i = 0;
	while (str[i] && !is_space(str[i])
		&& !is_operator(str[i])
		&& !is_single(str[i])
		&& !is_double(str[i]))
		i++;
	buff = ft_substr(str, 0, i);
	if (!buff)
		return (perror("Err: Malloc"), -1);
	new = ft_strjoin(last->value, buff);
	free(buff);
	if (!new)
		return (perror("Err: Malloc"), -1);
	free(last->value);
	last->value = new;
	return (i);
}

int	token_double_append(t_token *last, char *str)
{
	int		i;
	char	*buff;
	char	*new;

	i = 1;
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] != '"')
		return (printf("syntax error\n"), -1);
	buff = ft_substr(str, 1, i - 1);
	if (!buff)
		return (perror("Err: Malloc"), -1);
	new = ft_strjoin(last->value, buff);
	free(buff);
	if (!new)
		return (perror("Err: Malloc"), -1);
	free(last->value);
	last->value = new;
	return (i + 1);
}

int	token_single_append(t_token *last, char *str)
{
	int		i;
	char	*buff;
	char	*new;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] != '\'')
		return (printf("syntax error\n"), -1);
	buff = ft_substr(str, 1, i - 1);
	if (!buff)
		return (perror("Err: Malloc"), -1);
	new = ft_strjoin(last->value, buff);
	free(buff);
	if (!new)
		return (perror("Err: Malloc"), -1);
	free(last->value);
	last->value = new;
	last->dolar = -1;
	return (i + 1);
}
