/*
** game_info_serialization.h for Project-Master in /home/enach/CLionProjects/Bomberman/bm_test/include
**
** Made by hochar_n
** Login   <hochar_n@etna-alternance.net>
**
** Started on  Mon Jul  2 21:08:29 2018 hochar_n
** Last update Mon Jul  2 21:08:30 2018 hochar_n
*/

#ifndef  _GAME_INFO_SERIALIZATION_H_
# define _GAME_INFO_SERIALIZATION_H_

char		*serialize_game_info();
void		deserialize_game_info(char *serialized_game_info);
int		get_game_info_checksum();

#endif  /* !_GAME_INFO_SERIALIZATION_H_ */
