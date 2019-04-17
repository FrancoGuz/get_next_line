/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 10:19:37 by fguzman           #+#    #+#             */
/*   Updated: 2019/04/17 14:47:01 by fguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** This function does the same as strjoin, but it can free either or both strings after joining.
** This was made so that get_next_line is leak free.
*/

static char		*ft_strnjoin(char *s1, char *s2, int code)
{
	char *result;

	result = ft_strjoin(s1, s2);
	if (code == 1)
		free(s1);
	if (code == 2)
		free(s2);
	if (code == 3)
	{
		free(s1);
		free(s2);
	}
	return (result);
}

/*
** The function "process" is checked when get_next_line is reading the buffer and searching for newlines
** 
** It first checks if it read anything.
** if it did, then it checks if the pointer to result is NULL. If so, then it will point result to a dupe of buffer.
** else, it will point result to a joined result and buffer, with the joined result being freed(check strnjoin above).
** it will then check if my result at the current fd is not NULL and
** that the function that checks for the newline character is not NULL.
** We will then assign the pointer nl to the first instance of the newline
** character inside the result at the current fd.
** We will set the pointer nl to '\0', so we will only see everything up
** to the first new line inside the result as a null terminated string.
** We will then dupe that string to our line, then dupe everything after the first
** newline onto nl as a remainder. We will then free the remainder at that fd so we don't
** get any leaks. We then assign result at the current fd to equal nl, then we return 1. 
*/

static int		process(int bytes_read, char **result, char *buffer, char **l)
{
	char	*nl;

	nl = NULL;
	if (bytes_read > 0)
	{
		if (*result == NULL)
			*result = ft_strdup(buffer);
		else
			*result = ft_strnjoin(*result, buffer, 1);
	}
	if (*result != NULL && ft_strchr(*result, '\n') != NULL)
	{
		nl = ft_strchr(*result, '\n');
		nl[0] = '\0';
		*l = ft_strdup(*result);
		nl = ft_strdup(nl + 1);
		free(*result);
		*result = nl;
		return (1);
	}
	return (0);
}

/*
** get_next_line reads a file, and returns a line read up to the first instance of a newline character.
** returns 1 if it finds a line with a newline after it, 0 if its done reading or -1 if it finds an error with the file.
*/

int				get_next_line(const int fd, char **line)
{
	char			buffer[BUFF_SIZE + 1];
	int				br;
	static char		*r[4864];
	char			*temp;
	int				exit;
/*
** Here we are checking to see if the fd is less than 0, line is null 
** or if when reading the address of the buffer in the current fd
** at 0 bytes is less than 0, it will return -1.
*/
	if (fd < 0 || line == NULL || read(fd, &buffer, 0) < 0)
		return (-1);
/*
** This if statement is checked when it reads the entire file in one read.
** 
** Here we're checking if my result at the current fd is not NULL and
** that the function that checks for the newline character is not NULL.
** We will then assign the pointer temp to the first instance of the newline
** character inside the result at the current fd.
** We will set the pointer temp to '\0', so we will only see everything up
** to the first new line inside the result as a null terminated string.
** We will then dupe that string to our line, then dupe everything after the first
** newline onto temp as a remainder. We will then free the remainder at that fd so we don't
** get any leaks. We then assign result at the current fd to equal temp, then we return 1. 
*/
	if (r[fd] != NULL && ft_strchr(r[fd], '\n') != NULL)
	{
		temp = ft_strchr(r[fd], '\n');
		temp[0] = '\0';
		*line = ft_strdup(r[fd]);
		temp = ft_strdup(&temp[1]);
		free(r[fd]);
		return ((r[fd] = temp) == 0 ? 1 : 1);
	}
/**
** This while loop is while loop reads the file from the buffer.
**
** It first checks to see if bytes read is greater than 0 and that the buffer
** at the last position in the array is 0. If conditions are met, then it checks
** to see if exit equals 1 if the process function equals 1. Process works similar to
** what is going on in the if statement above.
*/
	while ((br = read(fd, &buffer, BUFF_SIZE)) > 0 &&
			(buffer[br] = '\0') == 0)
		if ((exit = process(br, &r[fd], buffer, line)) == 1)
			return (1);
/*
** This if statement is was made in the case that it doesn't find a newline character at the end of a line,
** or if if there isn't a EOF character. This returns the last line and nulls the file. Without this,
** my function was seg faulting if you give a file without newlines in it.
**
** This if statement is checked if bytes read is 0, and if result at the current fd exists
** and if the string length of the result is greater than 0, and if the pointer line 
** equal to result is the same as what line is currently pointing at, then we make remainder equal to null,
** and we return the last line. 
*/
	if (br == 0 && r[fd] && ft_strlen(r[fd]) > 0 && (*line = r[fd]) == *line)
		return ((r[fd] = NULL) == NULL) ? 1 : 1;
	return (0);
}
