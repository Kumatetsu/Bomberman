#ifndef _MOVING_H_
#define _MOVING_H_

void	move_player(t_game_info *game_info, t_player_request *player_request, int num_player);
void	change_sprite(t_player_info *player, int sprite_direction, int player_command);
int	check_collision(int requested_x, int requested_y, int num_player);

#endif /* !_MOVING_H_ */
