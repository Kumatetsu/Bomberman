/*
** game_info.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:40:22 2018 hochar_n
** Last update Thu Jul  5 21:40:22 2018 hochar_n
*/

#ifndef _GAME_INFO_H_
#define _GAME_INFO_H_

typedef struct		s_game_info
{
  int			tick_time;
  int			nb_client;
  int			game_status;
  int			id_client;
  t_player_info		players[4];
  t_map_destroyable	map_destroyable[195];
} t_game_info;

t_game_info	*get_game_info();
void		set_game_info(t_game_info *new_game_info);
void		create_game_info();
long		random_at_most(long max);
int		is_running();
void		start_game(t_srv **srv);

#endif /* !_GAME_INFO_H_ */
