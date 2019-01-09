#ifndef _MAP_MANAGEMENT_H_
#define _MAP_MANAGEMENT_H_

void	add_destructible_elements(t_game_info *game_info, int **map_pointer);
void	manage_bombs(t_game_info *game_info, int **map_pointer);
void	bomb_check_players(int i);
void	bomb_kill_player(int x, int y);
int		is_there_a_wall(t_game_info *game_info, int **map_pointer, int x, int y);

#endif /* !_MAP_MANAGEMENT_H_ */
