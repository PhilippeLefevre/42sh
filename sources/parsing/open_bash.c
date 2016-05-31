/*
** open_bash.c for open_bash in /home/puccio_c/rendu/minishell/my_42SH
** 
** Made by cyril puccio
** Login   <puccio_c@epitech.net>
** 
** Started on  Wed May 25 13:14:15 2016 cyril puccio
** Last update Tue May 31 14:54:20 2016 cyril puccio
*/

# include	"42.h"

t_bash          *push_bash(t_bash *list, char *data, char *name)
{
  t_node        *node;

  node = malloc(sizeof(*node));
  if (list != NULL && node != NULL)
    {
      if ((node->data = strdup(data)) == NULL)
	return (list);
      if ((node->name = strdup(name)) == NULL)
	return (list);
      node->next = NULL;
      node->p = false;
      if (list->tail == NULL)
	{
	  node->prev = NULL;
	  list->head = node;
	  list->tail = node;
	}
      else
	{
	  list->tail->next = node;
	  node->prev = list->tail;
	  list->tail = node;
	}
    }
  return (list);
}

int             check_quotes(char *str)
{
  int           i;
  int           nb;

  nb = 0;
  i = -1;
  while (str[++i])
    if (str[i] == '\'' || str[i] == '\"')
      nb++;
  return (nb == 2 ? nb : -1);
}

int		pars_bash(char *map, t_bash *bash)
{
  char		*name;
  char		*data;
  int		i;

  i = -1;
  name = "\0";
  data = "\0";
  if (strcmp("alias", my_strcut(map, 0, 5, 0)) == 0)
    {
      map += 6;
      while (map[++i] != '=' && map[i]);
      name = my_strcut(map, 0, i, 0);
      i++;
      if (map[i] && check_quotes(map) == 2
	  && (map[i] == '\'' || map[i] == '\"'))
	data = my_strcut(map, i + 1, strlen(map) - i - 2, 0);
    }
  else
    return (FAILURE);
  bash = push_bash(bash, data, name);
  return (SUCCESS);
}

char		*is_used(t_node *node, char *data)
{
  char		*str;

  str = NULL;
  while (node->name && node->next != NULL)
    {
      if (strcmp(node->name, data) == 0)
	return (str = node->data);
      node = node->next;
    }
  return (str);
}

char		*check_loop(t_bash *bash, char *cmd)
{
  t_node	*exe;
  t_bash	*tmp;
  char		*data;

  tmp = bash;
  exe = tmp->head;
  data = NULL;
  while (exe != NULL && exe->name && cmd)
    {
      if (strcmp(exe->name, cmd) == 0 && exe->p == false)
	{
	  exe->p = true;
	  data = is_used(tmp->head, exe->data);
	  (data == NULL ? data = exe->data : 0);
	  while (exe->prev != NULL)
	    exe = exe->prev;
	  tmp->head = exe;
	}
      exe = exe->next;
    }
  return (NULL);
}

char		*open_bash(char *arg, char *cmd)
{
  t_bash	bash;
  int           fd;
  char          *s;
  char		*ret;

  bash.head = NULL;
  ret = NULL;
  bash.tail = NULL;
  if ((fd = open(arg, O_RDONLY)) == -1)
    {
      fprintf(stderr, "Can't open file");
      my_exit(FAILURE);
    }
  while ((s = get_next_line(fd)))
    pars_bash(s, &bash);
  if ((ret = check_loop(&bash, cmd)) != NULL)
    return (ret);
  return (cmd);
}