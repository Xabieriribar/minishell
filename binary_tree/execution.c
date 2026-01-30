/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:50:04 by rick              #+#    #+#             */
/*   Updated: 2026/01/30 13:50:33 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
execute(node):
    if node.type == PIPE:
        create pipe
        fork left
        fork right
    else if node.type == COMMAND:
        apply redirections
        exec argv */