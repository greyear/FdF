
// TODO: header, check libs and definitions

#ifndef GET_NEXT_LINE_UTILS_H
# define GET_NEXT_LINE_UTILS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin_stash(char *stash, char *buf);
char	*ft_substrg(char *stash, unsigned int start, size_t len);
size_t	find_nl(char *stash);

#endif
