/*
** s for 42SH in /home/lefevr_h/Workspace/Github/42SH/sources/pipe
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Mon May 23 19:04:26 2016 Philippe Lefevre
** Last update Sun Jun 05 18:49:50 2016 Philippe Lefevre
*/

#include		"42.h"

int			prepare_pipe(t_cmd *cmd)
{
  t_cmd			*tmp;
  int			count_pipe;

  count_pipe = 0;
  tmp = cmd;
  while (tmp)
    {
      if (tmp->token == PIPE || (tmp->prev && tmp->prev->token == PIPE))
	{
	  tmp->go_on = 0;
	  count_pipe += 1;
	}
      tmp = tmp->next;
    }
  return (count_pipe);
}

int			exec_pipe(t_cmd *cmd, t_list *list, char **env,
				   int count[2])
{
  pid_t			pid;
  int			builtin;

  if (((cmd->fd = malloc(sizeof(int) * 2)) == NULL)
      || ((pipe(cmd->fd) == -1) || ((pid = fork()) == -1)))
    my_exit(fprintf(stderr, "Error: %s\n", strerror(errno)) * 0 + FAILURE);
  else if (pid == 0)
    {
      if (count[0] != 0)
	dup2(cmd->prev->fd[0], 0);
      if (count[0] < (count[1] - 1))
	dup2(cmd->fd[1], 1);
      if ((builtin = check_built(list, cmd)) == SUCCESS)
	my_exit(SUCCESS);
      normal_scatter(cmd, env, list, builtin - 20);
      my_exit(1);
    }
  list->value_exit = 0;
  if (count[0] != 0)
    close(cmd->prev->fd[0]);
  if (count[0] < count[1] - 1)
    close(cmd->fd[1]);
  return (list->value_exit);
}

int			scatter_pipe(t_cmd *cmd, t_list *list, char **env)
{
  t_cmd			*tmp;
  int			count[2];
  int			status;

  list->value_exit = 1;
  if ((count[1] = prepare_pipe(cmd)) == 0)
    return (FAILURE);
  tmp = cmd;
  count[0] = -1;
  while (++count[0] < count[1])
    {
      if ((list->value_exit = exec_pipe(tmp, list, env, count)) != SUCCESS)
	break;
      tmp = tmp->next;
    }
  tmp = cmd;
  count[0] = -1;
  while (++count[0] < count[1])
    {
      xfree(tmp->fd);
      tmp = tmp->next;
    }
  while ((status = waitpid(-1, 0, 0)) != -1);
  return (SUCCESS);
}
