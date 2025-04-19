#include "get_next_line.h"
#include <stdio.h>
int main()
{
	char *line = NULL;

	int fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	free(line);

	//special condition
	// for (int i = 0; i < 3; i++) //read half of the file
	// {
	// 	line = get_next_line(fd);
	// 	printf("%s", line);
	// 	free(line);
	// }
	// while ((line = get_next_line(fd)) != NULL) // clean up the rest of the file
	// 	free(line);
	/**
	 * need clean up because your static variable have leftover data
	 * if you don't clean up, it will cause memory leak
	*/

	close(fd);
	return (0);
}
