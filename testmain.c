#include "get_next_line.h"

/*
int		main(void)
{
	int	fd;
	int	fd2;
	char *line = NULL;

	fd = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	//read the first line from the first file
	get_next_line(fd, &line);
	printf("%s\n", line);

	//read the whole second file
	free(line);
	while(get_next_line(fd2, &line))
		printf("%s\n", line);

	//pick up from where the first left off and finish that file
	while(get_next_line(fd, &line))
		printf("%s\n", line);

	return (0);
}
*/

int	main(void)
{
	char *ptr;
	int fd;
	fd = open("hello.txt", O_RDONLY);
	printf("%d\n", fd);
	while (get_next_line(fd, &ptr) > 0)
	{
		printf("[%s]\n", ptr);
		ft_strdel(&ptr);
	}
	return (0);
}

/*
int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	char		*filename;

	filename = "../42FileChecker/srcs/gnl/gnl9_2.txt";
	fd = open(filename, O_RDONLY);
	if (fd > 2)
	{
		if (close(fd) == 0)
		{
			line = NULL;
			ret = get_next_line(fd, &line);
			if (ret != -1)
				printf("-> must have returned '-1' when receiving a closed file descriptor\n");
			else
				printf("OK\n");
		}
		else
		{
			printf("An error occured while closing file descriptor associated with file %s\n", filename);
			return (0);
		}
	}
	else
		printf("An error occured while opening file %s\n", filename);
	return (0);
}

*/
