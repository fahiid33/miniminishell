#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int	fd = open("test.txt", O_RDWR | O_CREAT, 0644);
	printf("%d\n", fd);
	close(fd);
	printf("after closing : %d\n", fd);
}
