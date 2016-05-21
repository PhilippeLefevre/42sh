/*
** print_env.c for  in /home/xx/Rendu/PSU/42SH
**
** Made by boris saint-bonnet
** Login   <saint-_o@epitech.net>
**
** Started on  Thu May 19 18:58:06 2016 boris saint-bonnet
** Last update Sat May 21 22:54:37 2016 Lucas Gambini
*/

# include "42.h"

int    print_env(t_list *list)
{
  t_node        *tmp;

  tmp = list->myEnv->head;
  if (list != NULL)
    {
      while (tmp != NULL)
	{
	  printf("%s=%s\n", tmp->name, tmp->data);
	  tmp = tmp->next;
	}
    }
  return (0);
}

void	print_prompt(t_list *list)
{
  char	*dirname;

  dirname = get_current_dir_name();
  write(1, GREEN, strlen(CYAN));
  if (find_user(list, "USER") == NULL)
    write(1, "user", strlen("user"));
  else
    write(1, find_user(list, "USER"), strlen(find_user(list, "USER")));
  write(1, ":", 1);
  write(1, CYAN, strlen(CYAN));
  write(1, dirname, strlen(dirname));
  write(1, " ", 1);
  write(1, DEFAULT, strlen(DEFAULT));
  free(dirname);
}
