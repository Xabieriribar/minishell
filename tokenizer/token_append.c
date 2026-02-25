/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:34:13 by rick              #+#    #+#             */
/*   Updated: 2026/02/25 11:02:48 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Creates and appends to the last node from the list.
+ Returns i, being the length of the added part of the string to.
+ this last node of the list, or a negative interger for error.*/
/* int	token_word_append(t_token *last, char *str, t_data *data)
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
	buff = expand_buff(buff, data);
	new = ft_strjoin(last->value, buff);
	free(buff);
	if (!new)
		return (perror("Err: Malloc"), -1);
	free(last->value);
	last->value = new;
	return (i);
} */

/*
* Creates and appends to the last node from the list,
* in case of finding double quotes.
+ Returns i, being the length of the added part of the string to.
+ this last node of the list, or a negative interger for error.*/
int	token_double_append(t_token *last, char *str, t_data *data)
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
	buff = expand_buff(buff, data);
	new = ft_strjoin(last->value, buff);
	free(buff);
	if (!new)
		return (perror("Err: Malloc"), -1);
	free(last->value);
	last->value = new;
	return (i + 1);
}

/*
* Creates and appends to the last node from the list,
* in case of finding single quotes.
+ Returns i, being the length of the added part of the string to.
+ this last node of the list, or a negative interger for error.*/
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


/*
* Creates and appends to the last node from the list.
+ Returns i, being the length of the added part of the string to.
+ this last node of the list, or a negative interger for error.*/
int	token_word_append(t_token *last, char *str, t_data *data)
{
	int		i;
	int		skip;
	char	*buff;
	char	*new;

	i = 0;
	skip = 0;
	while (str[i] && !is_space(str[i]) && !is_operator(str[i])
		&& !is_single(str[i]) && !is_double(str[i]))
	{
		if (str[i] == '$' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			skip = 1;
			break ;
		}
		i++;
	}
	buff = ft_substr(str, 0, i);
	buff = expand_buff(buff, data);
	new = ft_strjoin(last->value, buff);
	free(buff);
	free(last->value);
	last->value = new;
	return (i + skip);
}
