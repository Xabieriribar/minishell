/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:34:03 by rspinell          #+#    #+#             */
/*   Updated: 2025/11/24 09:58:18 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || 1 < 1)
	{
		if (stash)
			return (free_stash(&stash), NULL);
		return (NULL);
	}
	if (contains_n(stash))
	{
		line = get_lines(stash, '\n');
		stash = new_stash(stash);
		return (line);
	}
	line = _gnl(&stash, fd, 1);
	if (!line)
		return (NULL);
	if (contains_n(line))
		return (line);
	return (free_stash(&stash), line);
}

char	*_gnl(char **stash, int fd, int ret)
{
	char	*line;
	char	*buff;

	buff = ft_calloc_gnl(sizeof(char), (1 + 1));
	while (ret == 1)
	{
		ret = read(fd, buff, 1);
		if ((*stash == NULL || ft_strlen_gnl(*stash) == 0) && ret < 1)
		{
			if (*stash != NULL)
				free_stash(stash);
			return (free(buff), NULL);
		}
		*stash = concat_end(*stash, buff);
		buff = ft_calloc_gnl(sizeof(char), (1 + 1));
		if (contains_n(*stash))
		{
			line = get_lines(*stash, '\n');
			*stash = new_stash(*stash);
			return (free(buff), line);
		}
	}
	line = get_lines(*stash, '\0');
	return (free(buff), line);
}

/*
	* get_line() will allocate and copy a string until finding
	* a 'c' character and return the newly allocated string. */
char	*get_lines(char *str, char c)
{
	char	*line;
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (str[len] != c)
		len++;
	line = ft_calloc_gnl(sizeof(char), (len + 2));
	if (line == NULL)
		return (NULL);
	while (i <= len)
	{
		line[i] = str[i];
		i++;
	}
	return (line);
}

/*
	* concat_end concatenates at the end of stash, the buffer.
	* returns a newly reallocated stash with the buffer concat
	* in it or NULL if no memory available. */
char	*concat_end(char *stash, char *buff)
{
	int		ix;
	int		j;

	j = 0;
	if (!stash)
	{
		stash = ft_calloc_gnl(sizeof(char), (1 + 1));
		if (stash == NULL)
			return (NULL);
		ix = 0;
	}
	else
	{
		ix = ft_strlen_gnl(stash);
		stash = str_realloc(stash);
		if (!stash)
			return (NULL);
	}
	while (buff[j])
	{
		stash[ix] = buff[j];
		ix++;
		j++;
	}
	return (stash);
}

/*
	* function to get a new stash right after returning each line.
	* it will free the old stash and reallocate the new one with the string
	* right after the /n. */
char	*new_stash(char *str)
{
	char	*new;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (str[i] != '\n')
		i++;
	new = ft_calloc_gnl(sizeof(char), ft_strlen_gnl(str) - i);
	if (new == NULL)
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
		new[j] = str[i];
		i++;
		j++;
	}
	return (free(str), new);
}

// int	main(void)
// {
// 	int fd = open("tests/only_nl.txt", O_RDONLY);
// 	//printf("fd: %d\n", fd);
// 	char *str;
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// 	free(str);
// 	str = get_next_line(fd);
// 	free(str);
// }
// -------------------------------------------- //
// int main (void)
// {
// 	int fd = open("tests/read_error.txt", O_RDONLY);

// 	char *str;
// 	str = get_next_line(fd);
// 	printf("%s\n", str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf("%s\n", str);
// 	free(str);
// 	str = get_next_line(-1);
// 	printf("%s\n", str);
// 	close(fd);
// 	fd = open("tests/read_error.txt", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s\n", str);
// 		free(str);
// 	}
// 	free(str);
// }

/*
$	READ()

?	ssize_t read(int fd, void *buf, size_t nbyte);
	This function attempts to read nbyte bytes of data from the
	object referenced by the descriptor fd into the buffer
	pointed to by buf.  The read() function starts at a position
	given by the pointer associated with fd. At the end, the
	pointer is incremented by the number of bytes (nbyte) actually read.
*	Return
	On success, the number of bytes read is returned (zero indicates
    end of file), and the file position is advanced by this number.
	It is not an error if this number is smaller than the number of
    bytes requested; this may happen when fewer bytes are actually available.

$	OPEN:

?	int open(const char *path, int oflag, ... );

*Flags:
You have to tell your function what kind of access you want.

?    O_RDONLY: In read-only mode, open the file.
?    O_WRONLY: In a write-only mode, open the file
?    O_RDWR: Open the file in reading and write mode
?    O_CREAT: This flag is applied to create a file if it
?		doesn’t exist in the specified path or directory
?    O_EXCL: Prevents the file creation if it already
?		exists in the directory or location.

*Return:
The return value of open() is a file descriptor, a small,
nonnegative integer that is an index to an entry in the
process's table of open file descriptors. If there is an error somewhere,
the function will return -1 as a synonym of failure.
?	fd = open("text.txt", O_RDONLY);
*/
/*
$	IMPLEMENTATION

	- Allocate the buffer
	- Read the document.
	- Store in the buffer.
	- Copy the values of the buffer inside the static until
		static contains \n or the iteration of buffer is
		smaller than the size buffer (meaning we got till the
		end of the document).
	- Copy the values of the static until the \n into another
		string to return. Advance the static until \n + 1
		(This will have the static ready fo the next iteration).
*/
