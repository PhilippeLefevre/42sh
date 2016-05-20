/*
** string.c for  in /home/xx/Rendu/PSU/42SH/sources
** 
** Made by boris saint-bonnet
** Login   <saint-_o@epitech.net>
** 
** Started on  Thu May 19 23:24:51 2016 boris saint-bonnet
** Last update Fri May 20 04:48:16 2016 boris saint-bonnet
*/

# include "42.h"

char    *my_strcatc(char *path, char *command)
{
  char  *ret;
  int   i;
  int   j;

  if (path == NULL || command == NULL)
    return (NULL);
  if ((ret = malloc(sizeof(char) * (strlen(path) +
				    strlen(command) + 2))) == NULL)
    return (NULL);
  i = -1;
  while (path[++i] != '\0')
    ret[i] = path[i];
  ret[i++] = ' ';
  j = 0;
  while (command[j] != '\0')
    ret[i++] = command[j++];
  ret[i] = '\0';
  return (ret);
}

char            *my_epurstr(char *str)
{
  int           i;
  int           j;
  char          *epured;

  i = 0;
  j = 0;
  if ((epured = malloc(sizeof(epured) * strlen(str))) == NULL)
    return (NULL);
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  while (str[i])
    {
      if (str[i] == ' ' || str[i] == '\t')
	{
	  epured[j++] = ' ';
	  while (str[i] == ' ' || str[i] == '\t')
	    i++;
	}
      epured[j++] = str[i++];
    }
  epured[j] = '\0';
  if (epured[j - 1] == ' ')
    epured[j - 1] = '\0';
  return (epured);
}
