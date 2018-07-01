#ifndef  _GAME_INFO_SERIALIZATION_H_
# define _GAME_INFO_SERIALIZATION_H_

char		*serialize_game_info();
void		deserialize_game_info(char *serialized_game_info);
int		get_game_info_checksum();

#endif  /* !_GAME_INFO_SERIALIZATION_H_ */
