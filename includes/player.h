/*
** player.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:37:54 2018 hochar_n
** Last update Thu Jul  5 21:37:56 2018 hochar_n
*/

#ifndef _PLAYER_H_
#define _PLAYER_H_

int	add_player(t_srv **srv, int fd);
int	accept_players(t_srv **srv);
void	define_player_init_pos(t_player_info *player);
void	reset_players(t_srv **srv);

#endif /* !_PLAYER_H_ */
