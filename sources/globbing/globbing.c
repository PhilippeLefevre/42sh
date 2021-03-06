/*
** globbing.c for  in /home/hubert_i/rendu/2015/PSU/42SH
**
** Made by Hubert Leo
** Login   <hubert_i@epitech.net>
**
** Started on  Sat Jun  4 01:57:24 2016 Hubert Leo
** Last update Mon Jun  6 21:41:11 2016 cyril puccio
*/

#include "42.h"

int		need_globbing(char *src)
{
  int		i;

  i = -1;
  while (src[++i])
    {
      if (src[i] == '*' || src[i] == '?')
	return (1);
    }
  return (0);
}

char		*get_globbing(char *src)
{
  glob_t	globbuf;
  char		*result;
  int		i;

  globbuf.gl_offs = 0;
  result = "\0";
  i = 0;
  if (glob(src, GLOB_DOOFFS | GLOB_NOMATCH, NULL, &globbuf) != 0)
    return (NULL);
  while (globbuf.gl_pathv[i])
    {
      if (i != 0)
	result = get_fusion(result, " ");
      result = get_fusion(result, globbuf.gl_pathv[i]);
      i++;
    }
  xfree(src);
  i = 0;
  while (globbuf.gl_pathv[i])
    xfree(globbuf.gl_pathv[i++]);
  return (result);
}

char		*globbing(char *src, int i)
{
  char		**args;
  char		*result;
  char		*tmp;

  if (src == NULL || (args = my_str_to_wordtab(src, ' ')) == NULL)
    return (NULL);
  result = "\0";
  while (args[++i])
    {
      i != 0 ? result = get_fusion(result, " ") : 0;
      if (need_globbing(args[i]) == 1)
      	{
      	  if ((tmp = get_globbing(args[i])) == NULL)
	    {
	      fprintf(stderr, "%s: No match.\n", (i > 0) ? (args[i - 1])
		      : (args[i]));
	      return (NULL);
	    }
	  result = get_fusion(result, tmp);
      	}
      else
	result = get_fusion(result, args[i]);
    }
  xfree(args);
  return (result[0] == '\0' ? src : result);
}
