#include "libft.h"
#include <stdlib.h>

char	*ft_strldup(const char *s1, size_t len)
{
	char	*res;

	if (!s1)
		return (NULL);
	++len;
	res = (char *)malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len);
	return (res);
}