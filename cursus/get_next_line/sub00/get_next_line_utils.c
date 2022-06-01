#include "get_next_line.h"

// TODO: Consider removing the term argument from this function
// TODO: Protect malloc here
void	resize(char **arr, int old_len, int new_len)
{
	int		i;
	char	*new_arr;
	
	i = 0;
	// if (new_len == 0)
	// 	printf("NEW_LEN == 0\n");
	new_arr = ft_calloc(new_len, sizeof(char));
	// if (new_arr == NULL)
	// 	return (NULL);
	while (i < old_len && i < new_len)
	{
		new_arr[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	// if (term == TRUE)
	// 	new_arr[i] = '\0';
	*arr = new_arr;
	// return (arr)
}