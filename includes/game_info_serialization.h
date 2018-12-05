/*
** game_info_serialization.h for Project-Master in /home/enach/CLionProjects/Bomberman
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Thu Jul  5 21:40:27 2018 hochar_n
** Last update Thu Jul  5 21:40:28 2018 hochar_n
*/

#ifndef  _GAME_INFO_SERIALIZATION_H_
# define _GAME_INFO_SERIALIZATION_H_

char		*serialize_game_info();
void		deserialize_game_info(char *serialized_game_info);
int		get_game_info_checksum();

#endif  /* !_GAME_INFO_SERIALIZATION_H_ */
