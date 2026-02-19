/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:26:07 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 09:51:01 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Creates and appends node in case of finding an operator.
+ Returns the length of the sring "value".
+ or a negative interger for error.*/
int	token_operator(t_token **head, char *str, int ix)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (perror("Malloc error at token_operator()"), -1);
	set_init(token, str, ix, 3);
	if (!ft_strncmp(str, "<<", 2))
		token->value = ft_strdup("<<");
	else if (!ft_strncmp(str, ">>", 2))
		token->value = ft_strdup(">>");
	else if (!ft_strncmp(str, "|", 1))
		token->value = ft_strdup("|");
	else if (!ft_strncmp(str, "<", 1))
		token->value = ft_strdup("<");
	else if (!ft_strncmp(str, ">", 1))
		token->value = ft_strdup(">");
	else
		return (perror("Err: token_operator(S)"), free(token), -2);
	if (!token->value)
		return (perror("Malloc error at token_operator()"), free(token), -1);
	lst_add_back_token(head, token);
	return ((int)ft_strlen(token->value));
}

/*
* Creates and appends node in case of finding double quotes.
+ Returns the length of the sring "value".
+ or a negative interger for error. */
int	token_double(t_token **head, char *str, int ix)
{
	int		i;
	char	*buff;
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (perror("Err: Malloc"), -1);
	set_init(token, str, ix, 2);
	i = 0;
	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buff)
		return (perror("Err: Malloc"), free(token), -1);
	while (str[++i] && str[i] != '"')
		buff[i - 1] = str[i];
	if (str[i] != '"')
		return (free(buff), free(token), printf("syntax error"), -1);
	token->value = ft_strdup(buff);
	if (!token->value)
		return (perror("Err: Malloc"), free(token), free(buff), -1);
	lst_add_back_token(head, token);
	set_dolar(token);
	i = (int)ft_strlen(token->value);
	token->value = expander(token);
	return (free(buff), (i + 2));
}

/*
* Creates and appends node in case of finding single quotes.
+ Returns the length of the sring "value".
+ or a negative interger for error.*/
int	token_single(t_token **head, char *str, int ix)
{
	int		i;
	char	*buff;
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (perror("Err: Malloc"), -1);
	set_init(token, str, ix, 1);
	i = 0;
	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buff)
		return (perror("Err: Malloc"), free(token), -1);
	while (str[++i] && str[i] != '\'')
		buff[i - 1] = str[i];
	if (str[i] != '\'')
		return (free(buff), free(token), printf("syntax error"), -1);
	token->value = ft_strdup(buff);
	if (!token->value)
		return (perror("Err: Malloc"), free(token), free(buff), -1);
	lst_add_back_token(head, token);
	free(buff);
	set_dolar(token);
	return ((int)ft_strlen(token->value) + 2);
}

static bool	valid_c(char c)
{
	if (c && !is_single(c) && !is_double(c)
		&& !is_space(c) && !is_operator(c))
		return (true);
	return (false);
}

/*
* Creates and appends node in case of finding word.
+ Returns the length of the sring "value".
+ or a negative interger for error.*/
int	token_word(t_token **head, char *str, int ix)
{
	int		i;
	char	*buff;
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (perror("Err: Malloc"), -1);
	set_init(token, str, ix, 2);
	i = 0;
	buff = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buff)
		return (perror("Err: Malloc"), free(token), -1);
	while (valid_c(str[i]))
	{
		buff[i] = str[i];
		i++;
	}
	token->value = ft_strdup(buff);
	if (!token->value)
		return (perror("Err: Malloc"), free(token), free(buff), -1);
	lst_add_back_token(head, token);
	set_dolar(token);
	i = (int)ft_strlen(token->value);
	token->value = expander(token);
	return (free(buff), i);
}
