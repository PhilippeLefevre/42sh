/*
** parsing.h for  in /home/xx/Rendu/PSU/42SH
**
** Made by boris saint-bonnet
** Login   <saint-_o@epitech.net>
**
** Started on  Fri May 20 07:33:52 2016 boris saint-bonnet
** Last update Mon Jun 06 18:49:46 2016 Gambini Lucas
*/

#ifndef			_PARSING_H_
# define		_PARSING_H_

int                     check_variable(char *str);
int 			check_finish(char *s, char c, int nb);
int 			triple(char *s);
int 			check_bquotes(char *str);
int 			check_error(char *s);
char			*my_strcatc(char *path, char *command, int cond,
				    int bool);
char			*my_strcatenv(char *path, char *command);
char			*my_bquotes(char *str);
char			*doubles(char *s, char c);
char			*simples(char *s, char c);
char                    *set_variable(char *str, t_list *list);
char                    *replace_variable(char *str, t_list *list);
void			simple_space_after(t_pars *var);

char			**cmd_to_tab(char *line, char sp1, char sp2, char sp3);
char			**clean_tab(char **tab);
void			show_tab(char **tab);
void			free_tab(char **tab);
char			*open_bash(char *arg, char *cmd);
t_cmd			*swap_alias(t_cmd *cmd, t_bash *bash, int pos);

#endif			/* _PARSING_H_ */
