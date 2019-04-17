#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

int main(void)
{
	int fd;

	fd = open("test_file.txt", O_RDONLY);
	
	int bytes_read;
	char buffer[501];
	buffer[500] = '\0';
	int to_read = 500;

	bytes_read = read(fd, &buffer, to_read);
	buffer[bytes_read] = '\0';
	printf("BYTES_READ=%d\tIN_BUFFER='%s'\tFD=%d\tTO_READ=%d\n", bytes_read, buffer, fd, to_read);
	char *new_line_char = ft_strchr(buffer, '\n');
	printf("\nThe newline char is %d bytes in from start.\n", (int)(new_line_char - buffer));

	bytes_read = read(fd, &buffer, to_read);
	buffer[bytes_read] = '\0';
	printf("BYTES_READ=%d\tIN_BUFFER='%s'\tFD=%d\tTO_READ=%d\n", bytes_read, buffer, fd, to_read);
	return (0);
}
