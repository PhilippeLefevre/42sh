/*
** simple_exec.c for 42SH in /home/lefevr_h/Workspace/Github/42SH/sources/exec
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Mon May 23 23:00:09 2016 Philippe Lefevre
** Last update Mon Jun 06 22:06:59 2016 Philippe Lefevre
*/

# include		"42.h"

int			xwaitpid(int pid, int status, int opt)
{
  int			ret;

  ret = waitpid(pid, &status, opt);
  if (ret == -1)
    fprintf(stderr, "%s\n", strerror(errno));
  if (WIFEXITED(status))
    status = WEXITSTATUS(status);
  else
    print_signal_message(status);
  return (status);
}

char			*exec_find_secure_path(t_list *list, char *bin)
{
  t_node		*tmp;
  char			*cmd;
  struct stat		sb;

  tmp = list->myEnv->head;
  while (tmp != NULL)
    {
      if ((strcmp("PATH", tmp->name)) == 0)
	if (strlen(tmp->data) == 0)
	  return (bin);
      tmp = tmp->next;
    }
  if ((cmd = malloc(4 + strlen(bin) + 2)) == NULL)
    return (NULL);
  cmd = strcpy(cmd, "/bin/");
  cmd = strcat(cmd, bin);
  stat(cmd, &sb);
  if (!(access(cmd, F_OK)) && !((access(cmd, X_OK)))
      && (S_ISREG(sb.st_mode)))
    {
      xfree(bin);
      return (cmd);
    }
  xfree(cmd);
  return (bin);
}

char			*exec_find_path(t_path *path, char *bin)
{
  t_node		*tmp;
  char			*cmd;
  struct stat		sb;

  tmp = path->head;
  while (tmp != NULL && bin)
    {
      if ((cmd = malloc(strlen(tmp->data) + strlen(bin) + 2)) == NULL)
	return (NULL);
      cmd = strcpy(cmd, tmp->data);
      cmd = strcat(cmd, "/");
      cmd = strcat(cmd, bin);
      stat(cmd, &sb);
      if (!(access(cmd, F_OK)) && !((access(cmd, X_OK)))
	  && (S_ISREG(sb.st_mode)))
	{
	  xfree(bin);
	  return (cmd);
	}
      xfree(cmd);
      tmp = tmp->next;
    }
  return (bin);
}

int			simple_exec_builtin(t_list *list, t_cmd *cmd,
					    int	builtin)
{
  int			(*p[9])(t_list*, char**);

  p[0] = &builtin_cd;
  p[1] = &builtin_setenv;
  p[2] = &builtin_unsetenv;
  p[3] = &builtin_echo;
  p[4] = &builtin_exit;
  p[5] = &builtin_env;
  p[6] = &builtin_history;
  p[7] = &builtin_source;
  p[8] = &builtin_alias;
  if (p[builtin](list, cmd->cmd) == FAILURE)
    {
      check_go_on(cmd);
      return (FAILURE);
    }
  if (builtin != 4)
    list->value_exit = 0;
  return (SUCCESS);
}

int			simple_exec(t_cmd *cmd, t_list *list,
				    char **env, int builtin)
{
  struct stat		sb;

  list->value_exit = 1;
  if ((builtin += check_built(list, cmd, -1)) >= 0)
    return (simple_exec_builtin(list, cmd, builtin));
  if (list->path->head && list->path->head->data != NULL)
    {
      if ((cmd->cmd[0] = exec_find_path(list->path, cmd->cmd[0])) == NULL)
	return (FAILURE);
    }
  else
    {
      if ((cmd->cmd[0] = exec_find_secure_path(list, cmd->cmd[0])) == NULL)
	return (FAILURE);
    }
  if ((stat(cmd->cmd[0], &sb) != -1) && (S_ISREG(sb.st_mode))
      && (!(access(cmd->cmd[0], X_OK))
	  || (cmd->cmd[0][0] == '.' && cmd->cmd[0][1] == '/')))
    return (simple_exec2(cmd, list, env));
  fprintf(stderr, "%s: Command not found.\n", cmd->cmd[0]);
  check_go_on(cmd);
  return (FAILURE);
}
