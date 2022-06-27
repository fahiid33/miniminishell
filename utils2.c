#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

// char    *ft_strdup(s1)// s1, s2 char str[100000000] =  
// {
//     char    *dup;
//     int i;
//     int len;

//     i = 0;
//     len = strlen(s1);     // 
//     dup = malloc(sizeof(char ) * len + 1);
//     if (!dup)
//         return(NULL);
//     while (i < len)
//     {
//         dup[i] = s1[i];
//         i++;
//     }
//     dup[i] = '\0';
//     return (dup);
// }