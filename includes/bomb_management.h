#ifndef _BOMB_MANAGEMENT_H_
#define _BOMB_MANAGEMENT_H_

void			trigger_bomb(t_game_info *game_info,
				     int **map_pointer,
				     t_map_destroyable bomb);
void			apply_bomb_to_position(t_map_destroyable bomb,
					       int **map_pointer,
					       t_game_info *game_info,
					       int i);
void			destroy_bomb(t_game_info *game_info,
				     int **map_pointer,
				     t_map_destroyable bomb_to_destroy);
t_map_destroyable	get_element_at_pos(t_game_info *game_info,
					   int x,
					   int y);
int			apply_explosion(t_map_destroyable presence,
					t_map_destroyable bomb,
					t_game_info *game_info,
					int **map_pointer);

#endif /* !_BOMB_MANAGEMENT_H_ */
