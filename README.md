# Get_next_line
<p>this project is to create a function for C that return line by line from given file descriptor.</p>

## GUIDE FOR TEST THIS FUNCTION
### 1. you must create a file (main.c)
```
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
  close(fd);
  return (0);
}
```

### 2. create a text file (test.txt)
```
abc
def
ghi
jkl
mno
```

### 3. compile (two option)
i. default
```
  gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

ii. buffer size given (BUFFER_SIZE can be any size)
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c
```
 ( note: buffer size is to let the "read" function, how much buffer it need to read per line )


### 4. final you can execute with
```
./a.out
```
