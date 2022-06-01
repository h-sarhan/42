#include "get_next_line.h"

// TODO: Consider removing the term argument from this function
// TODO: Protect malloc here
void	resize(char **arr, int old_len, int new_len, int term)
{
	int		i;
	char	*new_arr;
	
	i = 0;
	new_arr = malloc(new_len);
	// if (new_arr == NULL)
	// 	return (NULL);
	while (i < old_len && i < new_len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	if (term == TRUE)
		new_arr[i] = '\0';
	*arr = new_arr;
	// return (arr)
}