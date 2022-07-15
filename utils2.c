#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "minishell.h"

int    is_piped(void)
{
    int i;

    i = 0;
	while (g_vars.line[i])
	{
		if (g_vars.line[i] == '|')
			return (1);
		i++;
	}
	return (0);
	
}