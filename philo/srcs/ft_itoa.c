#include "philosophers.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static long long	ft_abs_val(long long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static long long	ft_get_len(long long n)
{
	long long	len;

	len = 1;
	if (n < 0)
	{
		n = ft_abs_val(n);
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_lltoa(long long n)
{
	char		*str;
	long long	nb;
	long long	clone;
	long long	len;

	nb = n;
	clone = ft_abs_val(nb);
	len = ft_get_len(nb);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + clone % 10;
		clone /= 10;
		len--;
	}
	if (nb < 0)
		str[0] = '-';
	return (str);
}