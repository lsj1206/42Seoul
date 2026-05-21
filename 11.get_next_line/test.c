/* gccw -D BUFFER_SIZE=42 *.c */
#include <fcntl.h>
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*p;

	fd = open("test.txt", O_RDONLY);
	p = get_next_line(fd);
	printf("%s", p);
	free(p);
	printf("\n--------\n");
	p = get_next_line(fd);
	printf("%s", p);
	free(p);
	printf("\n--------\n");
	p = get_next_line(fd);
	printf("%s", p);
	free(p);
	printf("\n--------\n");
	return (0);
}
