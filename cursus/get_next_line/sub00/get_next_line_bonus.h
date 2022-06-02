
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define STDOUT 1
# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd);
void	*resize(char **arr, int old_len, int new_len);
char	*extract_line(int fd, char **line_buffer);
int		ft_strlen(char *str);
int		max(int a, int b);

#endif