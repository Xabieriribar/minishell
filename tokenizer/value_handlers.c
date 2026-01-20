/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:40:25 by rick              #+#    #+#             */
/*   Updated: 2026/01/20 11:46:00 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- All this functions will create a string according to the string
- recieved, separating like this all the different cases.

* - Words (normal characters)
* - Single quotes '...' (literal text)
* - Double quotes "..." (literal text, allows $ later)
* - Pipes |
* - Input redirection <
* - Output redirection >
* - Heredoc <<
* - Append redirection >>
* - Syntax error on unclosed quotes
*/