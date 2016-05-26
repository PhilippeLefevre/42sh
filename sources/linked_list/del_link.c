/*
** del_link.c for  in /home/xx/Rendu/PSU/42SH
**
** Made by boris saint-bonnet
** Login   <saint-_o@epitech.net>
**
** Started on  Wed May 25 22:59:19 2016 boris saint-bonnet
** Last update Thu May 26 15:10:27 2016 boris saint-bonnet
*/

#include "42.h"

void		free_node(t_node *tmp)
{
  free(tmp->data);
  free(tmp->name);
  free(tmp);
}

t_list		*del_first_link(t_list *list)
{
  t_node        *tmp;

  if (list != NULL)
    {
      tmp = list->myEnv->head;
      list->myEnv->head = tmp->next;
      tmp->next->prev = NULL;
    }
  return (list);
}

t_list		*del_last_link(t_list *list)
{
  t_node        *tmp;

  if (list != NULL)
    {
      tmp = list->myEnv->tail;
      list->myEnv->tail = tmp->prev;
      tmp->prev->next = NULL;
    }
  return (list);
}

t_list          *del_link(t_list *list, char *name)
{
  t_node        *tmp;

  tmp = list->myEnv->head;
  while (tmp != NULL)
    {
      if ((strcmp(name, tmp->name)) == 0)
	{
	  if (tmp != list->myEnv->head && tmp != list->myEnv->tail)
	    {
	      tmp->next->prev = tmp->prev;
	      tmp->prev->next = tmp->next;
	    }
	  else if (tmp == list->myEnv->head)
	    list = del_first_link(list);
	  else
	    list = del_last_link(list);
	}
      tmp = tmp->next;
    }
  return (list);
}
