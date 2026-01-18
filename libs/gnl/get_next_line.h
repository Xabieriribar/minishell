/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:34:42 by rspinell          #+#    #+#             */
/*   Updated: 2025/11/24 11:13:27 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*get_lines(char *str, char c);
char	*concat_end(char *stash, char *buff);
char	*new_stash(char *str);
char	*_gnl(char **stash, int fd, int ret);

int		ft_strlen_gnl(const char *s);
int		contains_n(char *str);
void	*ft_calloc_gnl(int nmemb, int size);
void	free_stash(char **stash);
char	*str_realloc(char *str);

#endif
