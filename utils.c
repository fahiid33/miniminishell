
#include "minishell.h"

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	dup = (char *)malloc(i + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcharjoin(char *s1, char c)
{
	int			i;
	i = 0;
	if (!s1)
		return (0);
	if (!c)
		return (s1);
	while (s1[i])
	{
		i++;
	}
	s1[i++] = c;
	s1[i] = '\0';
	return (s1);
}
	
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

