#include <unistd.h>

int	main()
{
	execlp("awk", "awk", "{count++} END {print count}", NULL);
}