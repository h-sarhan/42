#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("character.txt", O_WRONLY);

    write(fd, "hello", 5);
    close(fd);
}
