#ifndef _BOMB_MANAGEMENT_H_
#define _BOMB_MANAGEMENT_H_

int	index_to_x(int index);
int	index_to_y(int index);
int	coord_to_index(int x, int y);
int	get_target(t_map_destroyable bomb, int dir, int cases);
void	kill_payer(int id);
int	check_fire_effect(t_map_destroyable case_in_fire);
void	boom(t_map_destroyable *map_destroyable, int i);

#endif /* !_BOMB_MANAGEMENT_H_ */
